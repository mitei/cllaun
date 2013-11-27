#include "plugin.h"
#include "core.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>

#define c_engine cllaun::Core::Engine()

/*!
 * @brief プラグイン機能の初期化
 */
void cllaun::InitPlugin() {
    c_engine->globalObject().setProperty("plugin", c_engine->newObject());
}

/*!
 * @brief プラグイン・コマンドを実行する
 *
 * @param name プラグイン・コマンド名
 * @param args プラグイン・コマンドに渡す引数のリスト
 */
void cllaun::RunPluginCommand(const QString& name, cllaun::PluginArguments &args) {
    QScriptValue plugin = c_engine->globalObject().property("plugin").property(name);

    if (!plugin.isFunction()) /* Error! */ return;

    QScriptValueList arg_list;
    for (auto iter = args.begin(); iter != args.end(); ++iter) {
        arg_list.push_back(*iter);
    }

    plugin.call(c_engine->newObject(), arg_list);
}

/*!
 * @brief ネイティブプラグイン（.dll, .so）のロード
 *
 * @param engine ネイティブプラグインによって API を追加する対象の QScriptEngine インスタンス
 * @param name   読み込む Shared Library のファイルパス
 *
 * @return ロードしたライブラリのポインタ
 */
QLibrary* cllaun::LoadNativePlugin(const QString& path) {
    typedef void (*Initializer)(QScriptEngine*);

    QLibrary* lib = new QLibrary(path);
    if (!lib->load()) return nullptr;
    Initializer initializer = (Initializer)lib->resolve("Initialize");
    if (initializer == nullptr) return nullptr;
    initializer(c_engine);

    return lib;
}

/*!
 * @brief JavaScript ファイル（.js）を読み込んで実行
 *
 * @param engine JavaScript ファイルを実行する QScriptEngine インスタンス
 * @param path   実行する JavaScript ファイルのパス
 */
void cllaun::RunScriptFile(const QString& path) {
    QFile script_file(path);
    script_file.open(QFile::ReadOnly);
    QString str_script = QString::fromUtf8(script_file.readAll());
    QFileInfo script_info(script_file);
    c_engine->pushContext();
    c_engine->evaluate(str_script, script_info.fileName());
    c_engine->popContext();
}

#undef c_engine
