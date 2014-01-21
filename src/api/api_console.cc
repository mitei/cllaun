#include "api_console.h"
#include <QScriptValueIterator>
#include <QScriptEngine>


namespace {

/*!
 * @brief console.dir 関数
 *
 * モダンブラウザの console.dir 関数の模倣。
 * 完璧じゃないので暇な時に作り直し。
 */
QScriptValue consoleDir(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isObject()) {
        context->throwError(
                QScriptContext::TypeError, "Argument Error: argument 0 must be an Object.");
    }

    QScriptValueIterator itr(context->argument(0));
    while(itr.hasNext()) {
        itr.next();
        qDebug("%s: %s", itr.name().toStdString().c_str(), itr.value().toString().toStdString().c_str());
    }
    return QScriptValue(QScriptValue::UndefinedValue);
}

}

/*!
 * @brief Console-api の初期化
 */
cllaun::API_Console::API_Console(QScriptEngine* engine) {
    QScriptValue console_obj = engine->newObject();
    console_obj.setProperty("log", engine->globalObject().property("print"));
    console_obj.setProperty("dir", engine->newFunction(consoleDir));
    engine->globalObject().setProperty("console", console_obj);
}
