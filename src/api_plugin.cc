#include "api_plugin.h"
#include "plugin.h"
#include "api.h"

static QScriptValue Require(QScriptContext* context, QScriptEngine* engine) {
}

static QScriptValue Include(QScriptContext* context, QScriptEngine* engine) {

}

void cllaun::InitPlugin() {
    SetMethod("require", Requrie);
    SetMethod("include", Include);
}
