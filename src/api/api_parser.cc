#include "api_parser.h"

#include "api.h"
#include "command.h"
#include "parser.h"

Q_DECLARE_METATYPE(cllaun::Command::Type)

namespace {

using namespace cllaun;
using cllaun::Command;

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

QScriptValue typeToScriptValue(QScriptEngine* engine, const Command::Type& type) {
    switch (type) {
    case Command::INVALID:
        return QScriptValue("invalid");
    case Command::EXECUTABLE:
        return QScriptValue("executable");
    case Command::PLUGIN:
        return QScriptValue("plugin");
    case Command::PATH:
        return QScriptValue("path");
    case Command::ALIAS:
        return QScriptValue("alias");
    case Command::ANY:
        return QScriptValue("any");
    default:
        return QScriptValue("invalid");
    }
}

void typeFromScriptValue(const QScriptValue& obj, Command::Type& type) {
    QString type_str = obj.toString();
    if (type_str == "executable") {
        type = Command::EXECUTABLE;
    } else if (type_str == "plugin") {
        type = Command::PLUGIN;
    } else if (type_str == "path") {
        type = Command::PATH;
    } else if (type_str == "alias") {
        type = Command::ALIAS;
    } else if (type_str == "any") {
        type = Command::ANY;
    } else {
        type = Command::INVALID;
    }
}

}


cllaun::API_Parser::API_Parser(QScriptEngine* engine) {
    qScriptRegisterMetaType(engine, typeToScriptValue, typeFromScriptValue);
    QScriptValue parser_obj = engine->newObject();
    parser_obj.setProperty("parse", engine->newFunction(parserParse));
    parser_obj.setProperty("split", engine->newFunction(parserSplit));
    engine->globalObject().setProperty("Parser", parser_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}
