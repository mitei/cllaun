#pragma once

#include <QScriptEngine>
#include <QDebug>
#include "api.h"

static QScriptValue Print(QScriptContext* context, QScriptEngine* engine) {
    for (int i = 0; i < context->argumentCount(); ++i) {
        qDebug() << context->argument(i).toString();
    }
    return QScriptValue::UndefinedValue;
}

static void InitDebug(QScriptEngine* engine) {
    cllaun::SetMethod(engine, "print", Print);
}
