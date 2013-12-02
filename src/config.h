#pragma once

#include "dirs.h"

class QString;

namespace cllaun {

class Config {
public:
    // 指定された設定ファイルを読み込む
    void Read(const QString& conf_name);
    // TODO: comment
    inline void AddSearchPath(const QDir& dir) { search_paths << dir; }

public:
    // 設定ファイルの拡張子
    static const char* extension;
private:
    Dirs search_paths;
};

}
