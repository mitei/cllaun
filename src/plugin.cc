#include "plugin.h"

#include <QStringList>
#include <QString>
#include <QDir>

#include "api.h"
#include "core.h"
#include "dirs.h"


#define c_engine cllaun::Core::Engine()

/*!
 * @brief プラグインの拡張子
 */
const char* cllaun::Plugin::extension = ".js";

/*!
 * TODO
 */
cllaun::Plugin::Plugin(QObject* parent): QObject(parent) {
}

/*!
 * @brief 指定されたプラグインを読み込む
 *
 * @param name プラグイン名。plugins/（{プラグイン名}/{プラグイン名}.js）
 */
void cllaun::Plugin::read(const QString& name) {
    const Dirs search_dirs(search_paths);

    const QString plugin_dir_path = search_dirs.dirPath(name);
    if (!plugin_dir_path.isEmpty()) {
        const QDir plugin_dir(plugin_dir_path);
        const QString plugin_file_name = name + extension;
        if (plugin_dir.exists(plugin_file_name)) {
            load(plugin_dir.filePath(plugin_file_name));
        }
    }
}

/*!
 * @brief すべてのプラグインを読み込む
 */
void cllaun::Plugin::readAll() {
    QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
    QDir::SortFlags sort_flags = QDir::Name;

    Dirs search_dirs(search_paths);
    QStringList plugin_dir_list = search_dirs.entryList(filters, sort_flags);
    foreach (QString plugin_dir_path, plugin_dir_list) {
        const QDir plugin_dir(plugin_dir_path);
        const QString plugin_file_name = plugin_dir.dirName() + extension;
        if (plugin_dir.exists(plugin_file_name))
            load(plugin_dir.filePath(plugin_file_name));
    }
}

/*!
 * @brief 内部用、プラグインを読み込んで、読み込み済みプラグインの一覧に追加
 *
 * @param path 実行するスクリプトファイルのパス
 */
inline void cllaun::Plugin::load(const QString &path) {
    runScriptFile(path);
    loaded_plugin << path;
}

#undef c_engine
