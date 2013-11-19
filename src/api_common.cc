#include "api.h"
#include "api_common.h"
#include <QScriptEngine>
#include <QCoreApplication>

// アプリケーションを終了する
static QScriptValue Exit(QScriptContext* context, QScriptEngine* engine) {
    if (context->argumentCount() >= 1 &&
            context->argument(0).isNumber()) {
        qint32 exit_code = context->argument(0).toInt32();
        QCoreApplication::exit(exit_code);
    }
    else {
        QCoreApplication::exit(0);
    }
    return QScriptValue::UndefinedValue;
}

void cllaun::InitCommon(QScriptEngine* engine) {
    SetMethod(engine, "exit", Exit);
}

