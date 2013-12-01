#pragma once

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
private:
    static const char* extension;
    Plugin();
};

}
