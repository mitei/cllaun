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
 * @return 変換後の QScriptValueList
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

    // 第一引数が Command* でない場合、エラー
    if (command == nullptr) {
        context()->throwError(
                QScriptContext::TypeError, "Argument Error: argument 0 must be instance of Command.");
        return -1;
    }
    // Command::Type が INVALID の場合、何もしない
    if (command->getType() == Command::INVALID) {
        return -1;
    }

    // コマンド名を正規化
    QString name = normalize(*command);

    // コマンドタイプに応じて実行
    switch(command->getType()) {
    case Command::ANY:

    case Command::EXECUTABLE: {
        QStringList paths = qscriptvalue_cast<QStringList>(context()->thisObject().property("paths"));
        Dirs dirs(paths);
        QStringList name_filter;
        name_filter << (name + ".*");
        // ファイルまたは実行可能ファイルのみ検索
        QStringList entry_list = dirs.entryList(name_filter, QDir::Files|QDir::Executable);
        if (!entry_list.isEmpty()) {
            return execute(entry_list.at(0), command->getArgs().join(' '));
        } else if (command->getType() == Command::EXECUTABLE) {
            // コマンドタイプが EXECUTABLE かつ、Launcher.paths に指定されたコマンドを含む
            // ディレクトリが存在しない場合、実行すべきコマンドが存在しないため、何もしない
            return -1;
        }
    }

    case Command::ALIAS: {
        QScriptValue alias_obj = thisObject().property("aliases").property(name);
        if (alias_obj.isValid()) {
            // エイリアスが見つかった場合、別名を取得して新しい Command オブジェクトを生成、実行する
            QString alias = alias_obj.toString();
            Command new_command = Command(cllaun::Parser::type(alias), alias, command->getArgs());
            return run(&new_command);
        } else if (command->getType() == Command::ALIAS) {
            // コマンドタイプが ALIAS かつ、Launcher.aliases に指定されたエイリアスが存在しない場合、
            // 実行すべきコマンドが不明なため、何もしない
            return -1;
        }
    }

    case Command::PLUGIN: {
        QScriptValue command_obj = thisObject().property("commands").property(name);
        if (command_obj.isFunction()) {
            QStringList args = command->getArgs();
            // 引数がダブルクォートで囲まれている場合、ダブルクォートを取り除く
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
            // コマンドタイプが PLUGIN かつ、Launcher.commands に指定されたプラグイン・コマンドが存在しない場合、
            // 実行すべきプラグイン・コマンドが存在しないため、何もしない
            return -1;
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

    // コマンドタイプが PATH で、ダブルクォートで囲まれている場合、ダブルクォートを取り除く。
    // また、パスセパレータをプラットフォーム固有のセパレータに変換する。
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
