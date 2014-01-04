#include "api_config.h"

#include <QCoreApplication>
#include <QScriptEngine>
#include <QDir>

#include "api.h"
#include "config.h"

cllaun::API_Config::API_Config(QScriptEngine* engine) {
    Config* config = new Config(engine);
    config->dirs() << QCoreApplication::applicationDirPath()
                  << QDir::homePath();

    QScriptValue config_obj = engine->newQObject(config, QScriptEngine::AutoOwnership);
    engine->globalObject().setProperty("config", config_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}
