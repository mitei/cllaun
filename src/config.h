#pragma once

class QString;

namespace cllaun {

class Config {
public:
    static void Read(const QString& conf_name);
    static void ReadAll();
    static const char* extension;
private:
    Config();
};

}
