#include <QVector>
#include <QStringList>
#include <QString>
#include <QDir>

#include "api.h"
#include "core.h"

#include "plugin.h"


#define c_engine cllaun::Core::Engine()

/*!
 * @brief プラグインの拡張子
 */
const char* cllaun::Plugin::extension = ".js";

cllaun::Plugin::Plugin() {
    c_engine->globalObject().setProperty("plugin", c_engine->newObject());
}

/*!
 * @brief 指定されたプラグインを読み込む
 *
 * @param name プラグイン名。plugins/（{プラグイン名}/{プラグイン名}.js）
 */
void cllaun::Plugin::Read(const QString& name) {
    const QString plugin_dir_path = search_paths.DirPath(name);
    if (!plugin_dir_path.isEmpty()) {
        QDir plugin_dir(plugin_dir_path);
        const QString plugin_file_name = name + extension;
        if (plugin_dir.exists(plugin_file_name)) {
            Load(plugin_dir.filePath(plugin_file_name));
        }
    }
}

/*!
 * @brief すべてのプラグインを読み込む
 */
void cllaun::Plugin::ReadAll() {
    QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList plugin_dir_list = search_paths.EntryList(filters, sort_flags);
    foreach (QString plugin_dir_path, plugin_dir_list) {
        QDir plugin_dir(plugin_dir_path);
        const QString plugin_file_name = plugin_dir.dirName() + extension;
        if (plugin_dir.exists(plugin_file_name))
            Load(plugin_dir.filePath(plugin_file_name));
    }
}

// TODO: comment
inline void cllaun::Plugin::Load(const QString &path) {
    RunScriptFile(path);
    loaded_plugin << path;
}

#undef c_engine
