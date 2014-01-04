#include "api_console.h"

#include <QScriptValueIterator>
#include <QDebug>

#include "api.h"


namespace {

QScriptValue consoleDir(QScriptContext* context, QScriptEngine* engine) {
    if (!context->argument(0).isObject()) {
        // TODO: Error
        context->throwError("Argument Error: ");
    }

    QScriptValueIterator itr(context->argument(0));
    while(itr.hasNext()) {
        itr.next();
        qDebug("%s: %s", itr.name().toStdString().c_str(), itr.value().toString().toStdString().c_str());
    }
    return QScriptValue(QScriptValue::UndefinedValue);
}

}

cllaun::API_Console::API_Console(QScriptEngine* engine) {
    QScriptValue console_obj = engine->newObject();
    console_obj.setProperty("log", engine->globalObject().property("print"));
    console_obj.setProperty("dir", engine->newFunction(consoleDir));
    engine->globalObject().setProperty("console", console_obj);
}
