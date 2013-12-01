#pragma once

class QString;

namespace cllaun {

class Skin {
public:
    static void Read(const QString& name);
private:
    static const char* skin_file_name;
    Skin();
};

}
