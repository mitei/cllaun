#pragma once

#include <QFile>
#include <QFileInfo>
#include <QScriptEngine>
#include <QScriptContext>
#include <QScriptValue>

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
    static inline void setMethod(QScriptEngine* engine,
                                 const char* name,
                                 QScriptEngine::FunctionSignature func) {
        engine->globalObject().setProperty(name, engine->newFunction(func));
    }

    /*!
     * @brief グローバル関数を公開（FunctionWithArgSignature 版）
     *
     * @param engine 公開先のグローバルオブジェクトを持つ QScriptEngine*
     * @param name   JavaScript プロパティ名
     * @param func   公開したい C++ 関数
     * @param arg    func に渡す引数
     */
    static inline void setMethod(QScriptEngine* engine,
                                 const char* name,
                                 QScriptEngine::FunctionWithArgSignature func,
                                 void* arg) {
        engine->globalObject().setProperty(name, engine->newFunction(func, arg));
    }

    /*!
     * @brief RunScriptFile
     * @param path
     * @return
     */
    static inline QScriptValue runScriptFile(QScriptEngine* engine, const QString& path) {
        QFile script_file(path);
        script_file.open(QFile::ReadOnly);
        QString str_script = QString::fromUtf8(script_file.readAll());
        QFileInfo script_info(script_file);
        engine->pushContext();
        QScriptValue retv = engine->evaluate(str_script, script_info.fileName());
        engine->popContext();
        return retv;
    }
}
