#include "api_parser.h"
#include <QScriptEngine>
#include "command.h"
#include "parser.h"


Q_DECLARE_METATYPE(cllaun::Command::Type)

namespace {

using namespace cllaun;
using cllaun::Command;

/*!
 * @brief Parser.parse  パースを実行する
 * @return パースの実行結果の Command オブジェクト
 */
QScriptValue parserParse(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isString()) {
        context->throwError(
                QScriptContext::TypeError, "Argument Error: argument 0 must be a String.");
        return QScriptValue(QScriptValue::UndefinedValue);
    }
    Command* command = new Command(Parser::parse(context->argument(0).toString()));

    return engine->newQObject(command, QScriptEngine::AutoOwnership);
}

/*!
 * @brief Parser.split  コマンド文字列をトークン分割する
 * @return  各要素にトークン文字列を持つ配列
 */
QScriptValue parserSplit(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isString()) {
        context->throwError(
                QScriptContext::TypeError, "Argument Error: argument 0 must be a String.");
        return QScriptValue(QScriptValue::UndefinedValue);
    }

    return engine->toScriptValue(Parser::split(context->argument(0).toString()));
}


/*
 * Command::Type の C++ / Qt Script 間の変換関数
 */
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


/*!
 * @brief Parser-api の初期化
 */
cllaun::API_Parser::API_Parser(QScriptEngine* engine) {
    qScriptRegisterMetaType(engine, typeToScriptValue, typeFromScriptValue);
    QScriptValue parser_obj = engine->newObject();
    parser_obj.setProperty("parse", engine->newFunction(parserParse));
    parser_obj.setProperty("split", engine->newFunction(parserSplit));
    engine->globalObject().setProperty("parser", parser_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}
