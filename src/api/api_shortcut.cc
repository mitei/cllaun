#include "api_shortcut.h"
#include <QScriptEngine>
#include "shortcut_class.h"

cllaun::API_Shortcut::API_Shortcut(QScriptEngine* engine)
    : shortcut_cls(new ShortcutClass(engine))
{
    QScriptValue constructor = engine->newFunction(ShortcutClass::constructorFunc, shortcut_cls);
    constructor.setPrototype(engine->globalObject().property("Object").property("prototype"));
    engine->globalObject().setProperty("Shortcut", constructor,
                                       QScriptValue::ReadOnly|QScriptValue::Undeletable);
}

cllaun::API_Shortcut::~API_Shortcut() {
    delete shortcut_cls;
}
