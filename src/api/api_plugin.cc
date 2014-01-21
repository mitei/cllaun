#include "api_plugin.h"
#include <QScriptEngine>
#include "plugin.h"

/*!
 * @brief Plugin-api の初期化
 */
cllaun::API_Plugin::API_Plugin(QScriptEngine* engine) {
    QScriptValue plugin_obj = Plugin::newQObject(engine);
    engine->globalObject().setProperty(
                "plugin", plugin_obj, QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
