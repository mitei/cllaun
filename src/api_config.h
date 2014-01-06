#pragma once

class QScriptEngine;

namespace cllaun {

class Config;

class API_Config {
public:
    API_Config(QScriptEngine* engine);
    ~API_Config();
    static Config* globalConfig();
private:
    static Config* global_config;
private:
    API_Config();
};

}
