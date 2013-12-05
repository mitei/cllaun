#pragma once

#include <QStringList>
#include "dirs.h"

class QString;

namespace cllaun {

class Plugin {
public:
    // 指定されたプラグインを読み込む
    void Read(const QString& name);
    // すべてのプラグインを読み込む
    void ReadAll();
    // 読み込み済みプラグインの一覧
    inline const QStringList& LoadedPlugin() { return loaded_plugin; }
    // プラグインを検索するディレクトリを追加
    inline void AddSearchPath(const QDir& dir) { search_paths << dir; }

private:
    // 内部用、プラグイン読み込み
    void Load(const QString& path);

private:
    static const char* extension;   /*!< プラグインの拡張子 */
    QStringList loaded_plugin;      /*!< 読み込み済みのプラグイン一覧 */
    Dirs search_paths;              /*!< プラグイン検索ディレクトリの一覧 */
};

}
