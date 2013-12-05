#include "api.h"
#include "plugin.h"
#include "native_plugin.h"

#include "api_plugin.h"

static QScriptValue Require(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

static QScriptValue Include(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

void cllaun::InitPlugin() {
    /*
    QScriptEngine* engine = cllaun::Core::Engine();
    engine->globalObject().setProperty("plugin", engine->newObject());
    */
    SetMethod("require", Require);
    SetMethod("include", Include);
}
