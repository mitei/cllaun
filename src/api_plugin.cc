#include "api.h"
#include "plugin.h"

#include "api_plugin.h"

static QScriptValue Require(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

static QScriptValue Include(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

void cllaun::InitPlugin() {
    SetMethod("require", Require);
    SetMethod("include", Include);
}
