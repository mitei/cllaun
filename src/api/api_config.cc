#include "api_config.h"
#include <QCoreApplication>
#include <QScriptEngine>
#include <QDir>
#include "config.h"


cllaun::Config* cllaun::API_Config::global_config = nullptr;

/*!
 * @brief Config-api の初期化
 */
cllaun::API_Config::API_Config(QScriptEngine* engine) {
    QScriptValue config_obj = Config::newQObject(engine);
    global_config = qobject_cast<Config*>(config_obj.toQObject());

    QStringList default_dirs;
    default_dirs << QCoreApplication::applicationDirPath()
                 << QDir::homePath();
    config_obj.setProperty("dirs", qScriptValueFromSequence(engine, default_dirs));

    engine->globalObject().setProperty(
                "config", config_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}

// Config インスタンスへのグローバルアクセス
cllaun::Config* cllaun::API_Config::globalConfig() {
    return global_config;
}
