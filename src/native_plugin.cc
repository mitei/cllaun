#include "native_plugin.h"

#include <QLibrary>
#include <QScriptEngine>


cllaun::NativePlugin::NativePlugin() {
}

/*!
 * @brief デストラクタ
 *
 * ロードされたすべての DLL をアンロード
 */
cllaun::NativePlugin::~NativePlugin() {
    for (auto itr = plugins.begin(); itr != plugins.end(); ++itr) {
        Unload(itr);
    }
}

/*!
 * @brief DLL をロード
 *
 * @param path 読み込みたい DLL のパス
 *
 * @return 読み込んだ DLL のポインタ
 */
QLibrary* cllaun::NativePlugin::Load(const QString& name) {
    typedef void (*Initializer)(QScriptEngine*);

    QString plugin_dir_path = search_paths.dirPath(name);
    if (plugin_dir_path.isEmpty())
        return nullptr;

    QLibrary* lib = new QLibrary(plugin_dir_path);
    if (!lib->load())
        return nullptr;
    Initializer initializer = (Initializer)lib->resolve("Initializer");
    if (initializer == nullptr)
        return nullptr;
    plugins.insert(name, lib);
    return lib;
}

void cllaun::NativePlugin::Unload(Plugins::iterator itr) {
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
bool cllaun::NativePlugin::Unload(const QString& name) {
    Plugins::iterator itr = plugins.find(name);
    if (itr == plugins.end())
        return false;
    Unload(itr);
    return true;
}
