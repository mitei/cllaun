#pragma once

#include <QScriptEngine>

namespace cllaun {
    inline void SetMethod(QScriptEngine* engine, const char* name, QScriptEngine::FunctionSignature func) {
        engine->globalObject().setProperty(name, engine->newFunction(func));
    }
    inline void SetMethod(QScriptEngine* engine,const char* name,
                QScriptEngine::FunctionWithArgSignature func, void* arg) {
        engine->globalObject().setProperty(name, engine->newFunction(func, arg));
    }
}
