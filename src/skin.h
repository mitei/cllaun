#pragma once

class QString;

namespace cllaun {

class Skin {
public:
    // 指定されたスキンを読み込む
    static void Read(const QString& name);
private:
    // スキン本体の QSS の名前
    static const char* skin_file_name;
    Skin();
};

}
