#include <stdlib.h>

#include <QCoreApplication>

#include "api.h"

#include "api_common.h"

// アプリケーションを終了する
static QScriptValue Exit(QScriptContext* context, QScriptEngine* engine) {
    qint32 exit_code = context->argument(0).toInt32();
    QCoreApplication::exit(exit_code);
    exit(exit_code);

    return QScriptValue::UndefinedValue;
}

void cllaun::InitCommon() {
    SetMethod("exit", Exit);
}

