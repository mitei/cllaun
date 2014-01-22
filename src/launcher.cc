#include "launcher.h"
#include <QCoreApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include "parser.h"
#include "command.h"
#include "dirs.h"
#ifdef WIN32
#include <Windows.h>
#endif


namespace {

/*!
 * @brief QStringList から QScriptValueList への変換
 *
 * @param src 変換元の QStringList
 * @return 返還後の QScriptValueList
 */
QScriptValueList fromStringList(const QStringList& src) {
    QScriptValueList dest;
    foreach (const QString str, src) {
        dest << QScriptValue(str);
    }
    return dest;
}

}


/*!
 * @brief Launcher スクリプトオブジェクトの生成
 *
 * @param engine   オブジェクトの生成に使用するスクリプトエンジン
 * @return 生成した Launcher スクリプトオブジェクト
 */
QScriptValue cllaun::Launcher::newQObject(QScriptEngine* engine) {
    QScriptValue launcher_obj = engine->newQObject(new Launcher, QScriptEngine::ScriptOwnership);
    launcher_obj.setProperty("aliases", engine->newObject(), QScriptValue::Undeletable);
    launcher_obj.setProperty("commands", engine->newObject(), QScriptValue::Undeletable);
    launcher_obj.setProperty("paths", engine->newArray(), QScriptValue::Undeletable);
    return launcher_obj;
}

/*!
 * @brief コマンドを実行する
 *
 * @param command コマンド文字列
 * @return 実行結果
 */
int cllaun::Launcher::run(QObject* command_obj) {
    using cllaun::Command;

    Command* command = qobject_cast<Command*>(command_obj);

    // When argument 0 is not a Command object, throw Error.
    if (command == nullptr) {
        context()->throwError("Argument Error: argument 0 must be instance of Command.");
        return -1;
    }
    // When Command Type is INVALID, throw Error.
    if (command->getType() == Command::INVALID) {
        context()->throwError("Error: Command Type is INVALID.");
        return -1;
    }

    // get normalized command-name.
    QString name = normalize(*command);

    // run command.
    switch(command->getType()) {
    case Command::ANY:

    case Command::EXECUTABLE: {
        QStringList paths = qscriptvalue_cast<QStringList>(context()->thisObject().property("paths"));
        Dirs dirs(paths);
        QStringList name_filter;
        name_filter << (name + ".*");
        QStringList entry_list = dirs.entryList(name_filter, QDir::Files|QDir::Executable);
        if (!entry_list.isEmpty()) {
            return execute(entry_list.at(0), command->getArgs().join(' '));
        } else if (command->getType() == Command::EXECUTABLE) {
            return -1; // Error
        }
    }

    case Command::ALIAS: {
        QScriptValue alias_obj = thisObject().property("aliases").property(name);
        if (alias_obj.isValid()) {
            QString alias = alias_obj.toString();
            Command new_command = Command(cllaun::Parser::type(alias), alias, command->getArgs());
            return run(&new_command);
        } else if (command->getType() == Command::ALIAS) {
            return -1; // Error
        }
    }

    case Command::PLUGIN: {
        QScriptValue command_obj = thisObject().property("commands").property(name);
        if (command_obj.isFunction()) {
            QStringList args = command->getArgs();
            if (args.count() > 0) {
                for (int i = 0; i < args.size(); ++i) {
                    QString arg = args.at(i);
                    if (arg.startsWith('"') && arg.endsWith('"')) {
                        args.replace(i, arg.mid(1, arg.size() - 2));
                    }
                }
            }
            command_obj.call(QScriptValue(), fromStringList(args));
            return 0;
        } else if (command->getType() == Command::PLUGIN) {
            return -1; // Error
        }
    }

    case Command::PATH:
        return execute(name, command->getArgs().join(' '));

    default:
        return -1;
    }
}

/*!
 * @brief コマンドタイプに応じてコマンド名を修正して返す
 *
 * @param command 正規化するコマンドオブジェクト
 * @return 修正後のコマンド名
 */
QString cllaun::Launcher::normalize(const Command& command) {
    switch(command.getType()) {
    // ALIAS または PLUGIN の場合、接頭辞を取り除く
    case Command::ALIAS:
    case Command::PLUGIN:
        return command.getName().mid(1);

    // PATH かつ、ダブルクォートで囲まれている場合、ダブルクォートを取り除く
    case Command::PATH:
        return QDir::toNativeSeparators(
            command.getName().startsWith('"') && command.getName().endsWith('"') ?
                command.getName().mid(1, command.getName().size() - 2) :
                command.getName());
    default:
        return command.getName();
    }
}

#ifdef WIN32
/*!
 * @brief Windows 用 `ファイルを開く`
 *
 * @param path ファイルまたはディレクトリのパス
 * @param args 引数文字列
 * @return 実行結果
 */
int cllaun::Launcher::execute(const QString& path, const QString& args) {
    SHELLEXECUTEINFO sh_info;

    QFileInfo info(path);
    if (!info.exists()) return -1; // Error: path not exists.
    QDir dir(path);
    if (info.isFile()) dir.cdUp();
    QString directory = QDir::toNativeSeparators(dir.absolutePath());

    // set SHELLEXECUTEINFO(sh_info) members.
    sh_info.cbSize   = sizeof(SHELLEXECUTEINFO);
    //sh_info.fMask    = SEE_MASK_FLAG_NO_UI;
    sh_info.fMask    = NULL;
    sh_info.hwnd     = NULL;
    sh_info.lpVerb   = NULL; // "open"
    sh_info.lpFile   =
            reinterpret_cast<LPCTSTR>(QDir::toNativeSeparators(path).utf16());
    sh_info.lpParameters = (args != "") ?
            reinterpret_cast<LPCTSTR>(args.utf16()) :
            NULL;
    sh_info.lpDirectory = reinterpret_cast<LPCTSTR>(directory.utf16());
    sh_info.nShow = SW_NORMAL;
    sh_info.hInstApp = NULL;

    ShellExecuteEx(&sh_info);

    // TODO: return result
    return 1;
}
#endif

#ifdef __unix
/*!
 * @brief UNIX 用 execute
 *
 * @param path ファイルまたはディレクトリのパス
 * @param args 引数文字列
 * @return 実行結果
 */
int cllaun::Launcher::execute(const QString& path, const QString& args) {
    // TODO
    return 0;
}
#endif
