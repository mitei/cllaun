#pragma once

#include "dirs.h"

class QString;
class QApplication;

namespace cllaun {

class Skin {
public:
    Skin(QApplication* _app);
    // 指定されたスキンを読み込む
    void Read(const QString& name);
    // TODO: comment
    void AddSearchPath(const QDir& dir) { search_paths << dir; }

public:
    // スキン本体の QSS の名前
    static const char* skin_file_name;

private:
    Skin();

private:
    QApplication* app;
    Dirs search_paths;
};

}
