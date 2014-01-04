#include "api_commands.h"

#include "api.h"

cllaun::API_Commands::API_Commands(QScriptEngine *engine) {
    engine->globalObject().setProperty("commands", engine->newObject(), QScriptValue::Undeletable);
}
