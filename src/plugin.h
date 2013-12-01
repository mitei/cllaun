#pragma once

#include <QStringList>

class QString;

namespace cllaun {

class Plugin {
public:
    // プラグイン機能の初期化
    static void Initialize();
    // 指定されたプラグインを読み込む
    static void Read(const QString& name);
    // すべてのプラグインを読み込む
    static void ReadAll();
    // TODO: comment
    static inline const QStringList& LoadedPlugin() { return loaded_plugin; }

private:
    // TODO: comment
    static void Load(const QString& path);

private:
    // プラグインの拡張子
    static const char* extension;
    static QStringList loaded_plugin;
    Plugin();
};

}
