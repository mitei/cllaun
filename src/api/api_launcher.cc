#include "api_launcher.h"

#include "api.h"
#include "launcher.h"


cllaun::API_Launcher::API_Launcher(QScriptEngine* engine) {
    engine->globalObject().setProperty("Launcher", Launcher::newQObject(engine),
                                       QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
