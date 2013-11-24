#pragma once

#include <QScriptEngine>

namespace cllaun {
    inline void SetMethod(QScriptEngine* engine, QScriptValue* obj, const char* name, QScriptEngine::FunctionSignature func) {
        obj->setProperty(name, engine->newFunction(func));
    }
    inline void SetMethod(QScriptEngine* engine, QScriptValue* obj, const char* name,
                          QScriptEngine::FunctionWithArgSignature func, void* arg) {
        obj->setProperty(name, engine->newFunction(func, arg));
    }
    inline void SetMethod(QScriptEngine* engine, const char* name, QScriptEngine::FunctionSignature func) {
        engine->globalObject().setProperty(name, engine->newFunction(func));
    }
    inline void SetMethod(QScriptEngine* engine,const char* name,
                QScriptEngine::FunctionWithArgSignature func, void* arg) {
        engine->globalObject().setProperty(name, engine->newFunction(func, arg));
    }
    template <typename T>
    inline T* GetThis(QScriptContext* context) {
        return dynamic_cast<T*>(context->thisObject().toQObject());
    }
}
