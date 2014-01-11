#include "api_parser.h"

#include "api.h"
#include "command.h"
#include "parser.h"


namespace {

using namespace cllaun;

QScriptValue parserParse(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isString()) {
        //TODO: Error
        context->throwError("Argument Error:");
        return QScriptValue(QScriptValue::UndefinedValue);
    }

    Command* command = new Command(Parser::parse(context->argument(0).toString()));

    return engine->newQObject(command, QScriptEngine::AutoOwnership);
}

QScriptValue parserSplit(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isString()) {
        //TODO: Error
        context->throwError("Argument Error:");
        return QScriptValue(QScriptValue::UndefinedValue);
    }

    return engine->toScriptValue(Parser::split(context->argument(0).toString()));
}

}


cllaun::API_Parser::API_Parser(QScriptEngine* engine) {
    QScriptValue parser_obj = engine->newObject();
    parser_obj.setProperty("parse", engine->newFunction(parserParse));
    parser_obj.setProperty("split", engine->newFunction(parserSplit));
    engine->globalObject().setProperty("Parser", parser_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}
