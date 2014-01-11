#include "launcher.h"

#include <QCoreApplication>
#include <QProcess>
#include <QFileInfo>
#include <QDir>
#include <QScriptEngine>
#include <QDebug>

#include "parser.h"
#include "command.h"

#ifdef WIN32
#include <Windows.h>
#endif

QScriptValue cllaun::Launcher::newQObject(QScriptEngine* engine) {
    QScriptValue launcher_obj = engine->newQObject(new Launcher, QScriptEngine::ScriptOwnership);
    launcher_obj.setProperty("aliases", engine->newObject(), QScriptValue::Undeletable);
    launcher_obj.setProperty("commands", engine->newObject(), QScriptValue::Undeletable);
    return launcher_obj;
}

/*!
 * @brief コマンドを実行する
 *
 * @param command コマンド文字列
 *
 * @return 実行結果
 */
int cllaun::Launcher::run(QObject* command_obj) {
    using cllaun::Command;

    Command* command = qobject_cast<Command*>(command_obj);
    if (command == nullptr) {
        // TODO: Error
        context()->throwError("Argument Error:");
        return -1;
    }

    QString name;
    switch(command->getType()) {
    case Command::INVALID:
    case Command::ANY:
    case Command::EXECUTABLE:
        name = command->getName();
        break;
    case Command::ALIAS:
    case Command::PLUGIN:
        name = command->getName().mid(1);
        break;
    case Command::PATH:
        if (command->getName().startsWith('"') &&
            command->getName().endsWith('"')) {
            name = command->getName().mid(1, command->getName().size() - 2);
        } else {
            name = command->getName();
        }
        break;
    default:
        name = command->getName();
    }

    switch(command->getType()) {
    case Command::INVALID:
        return -1;

    case Command::ANY:

    case Command::EXECUTABLE:
        // TODO: implementation
        if (command->getType() == Command::EXECUTABLE)
            return -1;

    case Command::ALIAS: {
        // TODO: commenting
        QScriptValue alias_obj = thisObject().property("aliases").property(name);
        if (alias_obj.isValid()) {
            QString alias = alias_obj.toString();
            Command new_command = Command(cllaun::Parser::type(alias), alias, command->getArgs());
            return run(&new_command);
        } else if (command->getType() == Command::ALIAS) {
            // Error
            return -1;
        }
    }

    case Command::PLUGIN: {
        // TODO: commenting
        // TODO: implementation
        QScriptValue command_obj = thisObject().property("commands").property(name);
        if (command_obj.isFunction()) {
            QScriptValueList args;
            foreach(QString arg, command->getArgs()) {
                args << QScriptValue(arg);
            }
            command_obj.call(QScriptValue(), args);
        } else if (command->getType() == Command::PLUGIN) {
            // Error
            return -1;
        }
    }

    case Command::PATH:
        // TODO: implementation
    default:
        return -1;
    }
}

#ifdef WIN32
/*!
 * @brief Windows 用 `ファイルを開く`
 *
 * @param path ファイルまたはディレクトリのパス
 * @param args 引数文字列
 *
 * @return 実行結果
 */
int cllaun::Launcher::execute(const QString& path, const QString& args) {
    SHELLEXECUTEINFO sh_info;

    /*
     * set directory that contains path-file, as working-directory.
     */
    QDir dir(path);
    QFileInfo info(path);
    if (!info.isDir() && info.isFile())
        dir.cdUp();
    QString directory = QDir::toNativeSeparators(dir.absolutePath());

    /*
     * set SHELLEXECUTEINFO(sh_info) members.
     */
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
int cllaun::Launcher::execute(cosnt QString& path, const QString& args) {
    return 0;
}
#endif
