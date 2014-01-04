#include "api_module.h"

#include "api.h"


namespace {

QScriptValue requireFunc(QScriptContext* context, QScriptEngine* engine) {
    if (context->argumentCount() > 0) {
        QScriptValue module_id = context->argument(0);
        if (module_id.isString()) {

        }
    } else {
        // TODO: Error
    }
}

}


cllaun::API_Module::API_Module(QScriptEngine* engine) {
    QScriptValue require_func_obj = engine->newFunction(requireFunc);
}
