#pragma once

class QString;

namespace cllaun {

class Config {
public:
    void Read(const QString& conf_name);
    static const char* suffix;
private:
    Config();
};

}
