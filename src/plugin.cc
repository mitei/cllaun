#include "plugin.h"
#include <QDebug>
#include <QFile>
#include <QFileInfo>

/*!
 * @brief プラグイン機能の初期化
 */
void cllaun::InitPlugin(QScriptEngine* engine) {
    engine->globalObject().setProperty("plugin", engine->newObject());
}

/*!
 * @brief プラグイン・コマンドを実行する
 *
 * @param name プラグイン・コマンド名
 * @param args プラグイン・コマンドに渡す引数のリスト
 */
void cllaun::RunPluginCommand(QScriptEngine* engine, const QString& name, cllaun::PluginArguments &args) {
    QScriptValue plugin = engine->globalObject().property("plugin").property(name);

    if (!plugin.isFunction()) /* Error! */ return;

    QScriptValueList arg_list;
    for (auto iter = args.begin(); iter != args.end(); ++iter) {
        arg_list.push_back(*iter);
    }

    plugin.call(engine->newObject(), arg_list);
}

/*!
 * @brief ネイティブプラグイン（.dll, .so）のロード
 *
 * @param engine ネイティブプラグインによって API を追加する対象の QScriptEngine インスタンス
 * @param name   読み込む Shared Library のファイルパス
 *
 * @return ロードしたライブラリのポインタ
 */
QLibrary* cllaun::LoadNativePlugin(QScriptEngine* engine, const QString& path) {
    typedef void (*Initializer)(QScriptEngine*);

    QLibrary* lib = new QLibrary(path);
    if (!lib->load()) return nullptr;
    Initializer initializer = (Initializer)lib->resolve("Initialize");
    if (initializer == nullptr) return nullptr;
    initializer(engine);

    return lib;
}

/*!
 * @brief JavaScript ファイル（.js）を読み込んで実行
 *
 * @param engine JavaScript ファイルを実行する QScriptEngine インスタンス
 * @param path   実行する JavaScript ファイルのパス
 */
void cllaun::RunScriptFile(QScriptEngine* engine, const QString& path) {
    QFile script_file(path);
    script_file.open(QFile::ReadOnly);
    QString str_script = QString::fromUtf8(script_file.readAll());
    QFileInfo script_info(script_file);
    engine->pushContext();
    engine->evaluate(str_script, script_info.fileName());
    engine->popContext();
}
