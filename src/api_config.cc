#include "api_config.h"

#include <QCoreApplication>
#include <QScriptEngine>
#include <QDir>

#include "api.h"
#include "config.h"


cllaun::Config* cllaun::API_Config::global_config = nullptr;

cllaun::API_Config::API_Config(QScriptEngine* engine) {
    if (global_config == nullptr) {
        global_config = new Config(engine);
        global_config->dirs() << QCoreApplication::applicationDirPath()
                      << QDir::homePath();
    }

    QScriptValue config_obj = engine->newQObject(global_config);
    engine->globalObject().setProperty("config", config_obj,
                                       QScriptValue::Undeletable|QScriptValue::ReadOnly);
}

cllaun::API_Config::~API_Config() {
    delete global_config;
    global_config = nullptr;
}

cllaun::Config* cllaun::API_Config::globalConfig() {
    return global_config;
}
