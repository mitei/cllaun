#include <stdlib.h>

#include <QCoreApplication>

#include "api.h"

#include "api_common.h"

/*!
 * @brief アプリケーションを終了する
 *
 * @param context
 * @param engine
 *
 * @return 
 */
static QScriptValue Exit(QScriptContext* context, QScriptEngine* engine) {
    qint32 exit_code = context->argument(0).toInt32();

    // QCoreApplication::exec() を実行中でなければ意味が無い。
    // 設定ファイルやプラグインの読み込み中に exit() を呼べたほうが良いと思われるので
    // とりあえず stdlib の方も呼んでいる。
    QCoreApplication::exit(exit_code);
    exit(exit_code);

    return QScriptValue::UndefinedValue;
}

void cllaun::InitCommon() {
    SetMethod("exit", Exit);
}

