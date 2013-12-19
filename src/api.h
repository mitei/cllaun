#pragma once

#include "core.h"

#include <QFile>
#include <QFileInfo>
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>

#define c_engine cllaun::Core::engine()

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
    static inline void setMethod(const char* name,
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
    static inline void setMethod(const char* name,
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
    static inline T* getThis(QScriptContext* context) {
        return dynamic_cast<T*>(context->thisObject().toQObject());
    }

    /*!
     * @brief RunScriptFile
     * @param path
     * @return
     */
    static inline QScriptValue runScriptFile(const QString& path) {
        QFile script_file(path);
        script_file.open(QFile::ReadOnly);
        QString str_script = QString::fromUtf8(script_file.readAll());
        QFileInfo script_info(script_file);
        c_engine->pushContext();
        QScriptValue retv = c_engine->evaluate(str_script, script_info.fileName());
        c_engine->popContext();
        return retv;
    }
}

#undef c_engine
