#include "api_common.h"
#include <stdlib.h>
#include <QCoreApplication>
#include "api.h"


namespace {

/*!
 * @brief アプリケーションを終了する
 */
QScriptValue exitFunc(QScriptContext* context, QScriptEngine* engine) {
    qint32 exit_code = context->argument(0).toInt32();

    // QCoreApplication::exec() を実行中でなければ意味が無い。
    // 設定ファイルやプラグインの読み込み中に exit() を呼べたほうが良いと思われるので
    // とりあえず stdlib の方も呼んでいる。
    QCoreApplication::exit(exit_code);
    exit(exit_code);

    return QScriptValue::UndefinedValue;
}

/*!
 * @brief eval 関数
 */
QScriptValue evalFunc(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isString()) {
        //TODO: Error
        context->throwError("Argument Error:");
    }

    const QString script_str = context->argument(0).toString();
    return engine->evaluate(script_str);
}

}

/*!
 * @brief Common-api の初期化
 */
cllaun::API_Common::API_Common(QScriptEngine *engine) {
    setMethod(engine, "exit", exitFunc);
    setMethod(engine, "eval", evalFunc);
}

