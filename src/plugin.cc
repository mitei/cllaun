#include "plugin.h"
#include "api.h"
#include "core.h"
#include <QString>
#include <QDir>

#define c_engine cllaun::Core::Engine()

const char* cllaun::Plugin::extension = ".js";

/*!
 * @brief プラグイン機能の初期化
 */
void cllaun::Plugin::Initialize() {
    c_engine->globalObject().setProperty("plugin", c_engine->newObject());
}

/*!
 * @brief 指定されたプラグインを読み込む
 *
 * @param name プラグイン名。plugins/（{プラグイン名}/{プラグイン名}.js）
 */
void cllaun::Plugin::Read(const QString& name) {
    const QVector<QDir> dirs = Core::PluginDirs();
    QString fname = name + extension;

    foreach (auto dir, dirs) {
        if (dir.cd(name) && dir.exists(fname)) {
            RunScriptFile(dir.filePath(fname));
        }
    }
}

/*!
 * @brief すべてのプラグインを読み込む
 */
void cllaun::Plugin::ReadAll() {
    const QVector<QDir> dirs = Core::PluginDirs();

    foreach (auto dir, dirs) {
        QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
        QDir::SortFlags sort_flags = QDir::Name;

        QStringList plugin_dir_list = dir.entryList(filters, sort_flags);
        foreach (auto plugin_dir_name, plugin_dir_list) {
            QDir plugin_dir(dir);
            plugin_dir.cd(plugin_dir_name);
            QString plugin_file_name = plugin_dir.dirName() + extension;
            if (plugin_dir.exists(plugin_file_name)) {
                RunScriptFile(plugin_dir.filePath(plugin_file_name));
            }
        }
    }
}

#undef c_engine
