#include "plugin_manager.h"
#include "plugin.h"
#include <QScriptEngine>

cllaun::PluginManager::PluginManager(QScriptEngine* engine_): engine(engine_) {
}

/*!
 * @brief デストラクタ
 *
 * ロードされたすべての DLL をアンロード
 */
cllaun::PluginManager::~PluginManager() {
    for (Plugins::iterator itr = plugins.begin(); itr != plugins.end(); ++itr) {
        Unload(itr);
    }
}

void cllaun::PluginManager::SetEngine(QScriptEngine* engine_) {
    engine = engine_;
}

/*!
 * @brief DLL をロード
 *
 * @param path 読み込みたい DLL のパス
 *
 * @return 読み込んだ DLL のポインタ
 */
QLibrary* cllaun::PluginManager::Load(const QString& path) {
    QLibrary* lib = LoadNativePlugin(engine, path);
    if (lib != nullptr) {
        plugins.insert(path, lib);
    }
    return lib;
}

void cllaun::PluginManager::Unload(Plugins::iterator itr) {
    (*itr)->unload();
    delete (*itr);
    plugins.erase(itr);
}

/*!
 * @brief DLL をアンロード
 *
 * @param path アンロードしたい DLL のパス
 *
 * @return アンロードに成功したら true
 */
bool cllaun::PluginManager::Unload(const QString &path) {
    Plugins::iterator itr = plugins.find(path);
    if (itr == plugins.end())
        return false;
    Unload(itr);
    return true;
}
