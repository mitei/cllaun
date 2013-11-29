#pragma once

class QString;

namespace cllaun {

class Config {
public:
    // 指定された設定ファイルを読み込む
    static void Read(const QString& conf_name);
    // すべての設定ファイルを読み込む
    static void ReadAll();
    // 設定ファイルの拡張子
    static const char* extension;
private:
    Config();
};

}
