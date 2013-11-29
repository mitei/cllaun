#include "plugin.h"
#include "api.h"
#include "core.h"
#include <QString>
#include <QDir>

#define c_engine cllaun::Core::Engine()

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
    auto dirs = Core::PluginDirs();

    for (auto iter = dirs.begin(); iter != dirs.end(); ++iter) {
        QDir dir(*iter + QDir::separator() + name);
        if (dir.exists(name + ".js")) {
            RunScriptFile(dir.filePath(name + ".js"));
        }
    }
}

/*!
 * @brief すべてのプラグインを読み込む
 */
void cllaun::Plugin::ReadAll() {
    auto dirs = Core::PluginDirs();

    for (auto iter = dirs.begin(); iter != dirs.end(); ++iter) {
        QDir dir(*iter);
        QStringList pdir_list = dir.entryList(QDir::Dirs|QDir::NoDotAndDotDot, QDir::Name);

        for (auto iter2 = pdir_list.begin(); iter2 != pdir_list.end(); ++iter2) {
            QDir pdir(dir.dirName() + QDir::separator() + (*iter2));
            if (pdir.exists(pdir.dirName() + ".js")) {
                RunScriptFile(pdir.filePath(pdir.dirName() + ".js"));
            }
        }
    }
}

#undef c_engine
