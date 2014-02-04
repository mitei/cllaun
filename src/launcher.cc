#include "launcher.h"
#include <QCoreApplication>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <QScriptEngine>
#include <QScriptValueIterator>
#include "parser.h"
#include "dirs.h"

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
        QStringList paths = qscriptvalue_cast<QStringList>(thisObject().property("paths"));
        Dirs dirs(paths);
        QStringList name_filter;
        name_filter << (name + "*");
        // ファイルまたは実行可能ファイルのみ検索
        QStringList entry_list = dirs.entryList(name_filter, QDir::Files|QDir::Executable);
        if (!entry_list.isEmpty()) {
            const QString name = entry_list.at(0);
            if (QProcess::startDetached(name, command->getArgs())) {
                return 0;
            } else {
                QDesktopServices::openUrl(QUrl::fromLocalFile(name));
            }
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

    case Command::PATH: {
        QFileInfo path_info(name);
        if (path_info.exists()) {
            if (path_info.isExecutable()) {
                if (QProcess::startDetached(name, command->getArgs())) {
                    return 0;
                }
            }
            return QDesktopServices::openUrl(QUrl::fromLocalFile(name)) ? 0 : -1;
        }
    }

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
    return normalize(command.getType(), command.getName());
}

QString cllaun::Launcher::normalize(const QString& name) {
    return normalize(Parser::type(name), name);
}

QString cllaun::Launcher::normalize(cllaun::Command::Type type, const QString& name) {
    switch(type) {
    // ALIAS または PLUGIN の場合、接頭辞を取り除く
    case Command::ALIAS:
    case Command::PLUGIN:
        return name.mid(1);

    // コマンドタイプが PATH で、ダブルクォートで囲まれている場合、ダブルクォートを取り除く。
    // また、パスセパレータをプラットフォーム固有のセパレータに変換する。
    case Command::PATH:
        return QDir::toNativeSeparators(
            name.startsWith('"') && name.endsWith('"') ?
                name.mid(1, name.size() - 2) :
                name);
    default:
        return name;
    }
}

/*!
 * @brief 指定されたコマンドタイプのコマンド候補リストを取得
 *
 * @param type  検索するコマンドの種類
 * @param name  コマンド名（またはコマンド名の先頭N文字）
 * @return  一致したコマンドのリスト。見つからなかった場合は空のリスト。
 */
QStringList cllaun::Launcher::list(cllaun::Command::Type type, const QString& name) {
    QStringList candidates;

    switch (type) {
    case Command::ANY:
    case Command::EXECUTABLE: {
        QStringList paths = qscriptvalue_cast<QStringList>(thisObject().property("paths"));
        Dirs dirs(paths);
        QStringList name_filter = QStringList() << (name + "*");
        // ファイルまたは実行可能ファイルのみ検索
        QStringList entry_list = dirs.entryList(name_filter, QDir::Files|QDir::Executable);
        if (!entry_list.isEmpty()) {
            candidates += entry_list;
        }

        // Command type が EXECUTABLE の場合、検索終了
        if (type == Command::EXECUTABLE) break;
    }

    case Command::ALIAS: {
        QScriptValue aliases_obj = thisObject().property("aliases");
        QScriptValueIterator iter(aliases_obj);
        while (iter.hasNext()) {
            iter.next();
            if (iter.name().startsWith(name, Qt::CaseInsensitive)) {
                candidates.push_back('?' + iter.name());
            }
        }

        // Command type が ALIAS の場合、検索終了
        if (type == Command::ALIAS) break;
    }

    case Command::PLUGIN: {
        QScriptValue commands_obj = thisObject().property("commands");
        QScriptValueIterator iter(commands_obj);
        while (iter.hasNext()) {
            iter.next();
            if (iter.name().startsWith(name, Qt::CaseInsensitive)) {
                candidates.push_back(':' + iter.name());
            }
        }

        // Command type が PLUGIN の場合、検索終了
        if (type == Command::PLUGIN) break;
    }

    case Command::PATH: {
        QFileInfo path_info(name);
        QStringList name_filter = QStringList() << (path_info.fileName() + "*");
        QStringList filename_list = path_info.dir().entryList(name_filter, QDir::NoDotAndDotDot|QDir::Files|QDir::Dirs);
        // ディレクトリ名を含む絶対パスに変換して候補リストに追加
        foreach (const QString filename, filename_list) {
            QString absolute_path = path_info.absolutePath();
            if (!absolute_path.endsWith('/')) absolute_path += '/';
            absolute_path = QDir::toNativeSeparators(absolute_path + filename);
            candidates.push_back(absolute_path.replace(" ", "\\ "));
        }

        // Command type が PATH の場合、検索終了
        if (type == Command::PATH) break;
    }

    default:
        break;
    }

    return candidates;
}

/*!
 * @brief コマンド候補リストを取得
 *
 * @param src  検索するコマンド名（またはコマンド名の先頭N文字）
 *
 * @return  一致したコマンドのリスト
 */
QStringList cllaun::Launcher::list(const QString& src) {
    Command::Type type = Parser::type(src);
    return list(type, normalize(type, src));
}
