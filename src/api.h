#pragma once

#include "core.h"
#define c_engine cllaun::Core::Engine()

/*
 * API 公開に便利な関数など
 */

namespace cllaun {
    /*!
     * @brief グローバル関数を公開（FunctionSignature 版）
     *
     * @param engine 公開先のグローバルオブジェクトを持つ QScriptEngine*
     * @param name   JavaScript プロパティ名
     * @param func   公開したい C++ 関数
     */
    inline void SetMethod(const char* name,
                          QScriptEngine::FunctionSignature func) {
        c_engine->globalObject().setProperty(name, c_engine->newFunction(func));
    }

    /*!
     * @brief グローバル関数を公開（FunctionWithArgSignature 版）
     *
     * @param engine 公開先のグローバルオブジェクトを持つ QScriptEngine*
     * @param name   JavaScript プロパティ名
     * @param func   公開したい C++ 関数
     * @param arg    func に渡す引数
     */
    inline void SetMethod(const char* name,
                          QScriptEngine::FunctionWithArgSignature func,
                          void* arg) {
        c_engine->globalObject().setProperty(name, c_engine->newFunction(func, arg));
    }

    /*!
     * @brief QObject を継承したクラスから生成した QScriptValue から元のオブジェクトを取り出す
     *
     * @tparam T      thisObject の元の型
     * @param context thisObject を取り出すコンテキスト
     *
     * @return        元のオブジェクト
     */
    template <typename T>
    static inline T* GetThis(QScriptContext* context) {
        return dynamic_cast<T*>(context->thisObject().toQObject());
    }
}

#undef c_engine
