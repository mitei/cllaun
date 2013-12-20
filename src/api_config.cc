#include "api_config.h"

#include <QCoreApplication>
#include <QDir>

#include "api.h"
#include "config.h"

void cllaun::initConfig() {
    Config* config = new Config();
    config->dirs() << QCoreApplication::applicationDirPath()
                  << QDir::homePath();

    QScriptValue config_obj = cllaun::Core::engine()->newQObject(config, QScriptEngine::AutoOwnership);
    cllaun::Core::engine()->globalObject().setProperty("config", config_obj);
}
