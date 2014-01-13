#include "shortcut.h"

#include <QScriptEngine>


cllaun::Shortcut::Shortcut(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
    // TODO
}

QScriptClass::QueryFlags cllaun::Shortcut::queryProperty(
        const QScriptValue& object,
        const QScriptString& name,
        QueryFlags flags,
        uint* id)
{
    // TODO
    return flags;
}

QScriptValue cllaun::Shortcut::property(
        const QScriptValue &object,
        const QScriptString& name,
        uint id)
{
    // TODO
    return QScriptValue();
}

void cllaun::Shortcut::setProperty(
        QScriptValue& object,
        const QScriptString& name,
        uint id,
        const QScriptValue& value)
{
    // TODO
}

QScriptValue cllaun::Shortcut::constructorFunc(
        QScriptContext* context, QScriptEngine* engine)
{
    if (!context->argument(0).isQObject()) {
        context->throwError("Argument Error: argument 0 must be an parent Widget.");
        return QScriptValue();
    }
    // TODO
    return QScriptValue();
}
