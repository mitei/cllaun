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
    // TODO: comment
    inline const QStringList& LoadedPlugin() { return loaded_plugin; }
    // TODO: comment
    inline void AddSearchPath(const QDir& dir) { search_paths << dir; }

private:
    // TODO: comment
    void Load(const QString& path);

private:
    // プラグインの拡張子
    static const char* extension;
    // TODO: comment
    QStringList loaded_plugin;
    // TODO: comment
    Dirs search_paths;
};

}
