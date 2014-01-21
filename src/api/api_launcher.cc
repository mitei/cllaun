#include "api_launcher.h"
#include <QScriptEngine>
#include "launcher.h"


/*!
 * @brief Launcher-api の初期化
 */
cllaun::API_Launcher::API_Launcher(QScriptEngine* engine) {
    engine->globalObject().setProperty("Launcher", Launcher::newQObject(engine),
                                       QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
