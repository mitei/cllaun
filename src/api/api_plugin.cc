#include "api_plugin.h"

#include "api.h"
#include "plugin.h"

cllaun::API_Plugin::API_Plugin(QScriptEngine* engine) {
    QScriptValue plugin_obj = Plugin::newQObject(engine);
    engine->globalObject().setProperty(
                "plugin", plugin_obj, QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
