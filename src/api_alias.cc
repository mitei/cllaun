#include "api_alias.h"

#include "api.h"

cllaun::API_Alias::API_Alias(QScriptEngine *engine) {
    engine->globalObject().setProperty("alias", engine->newObject(), QScriptValue::Undeletable);
}
