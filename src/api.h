#pragma once

#include <QScriptEngine>

namespace cllaun {
    // FunctionSignature 版
    inline void SetMethod(QScriptEngine* engine, const char* name, QScriptEngine::FunctionSignature func) {
        engine->globalObject().setProperty(name, engine->newFunction(func));
    }
    // FunctionWithArgSignature 版
    inline void SetMethod(QScriptEngine* engine,const char* name,
                QScriptEngine::FunctionWithArgSignature func, void* arg) {
        engine->globalObject().setProperty(name, engine->newFunction(func, arg));
    }
}
