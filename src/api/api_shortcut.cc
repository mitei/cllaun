#include "api_shortcut.h"
#include <QScriptEngine>
#include "shortcut_class.h"
#include "widget/widget.h"

cllaun::ShortcutClass* cllaun::API_Shortcut::shortcut_cls = nullptr;

cllaun::API_Shortcut::API_Shortcut(QScriptEngine* engine)
{
    if (shortcut_cls == nullptr) {
        shortcut_cls = new ShortcutClass(engine);
    }
    /*
    QScriptValue constructor = engine->newFunction(ShortcutClass::constructorFunc, shortcut_cls);
    constructor.setPrototype(engine->globalObject().property("Object").property("prototype"));
    engine->globalObject().setProperty("Shortcut", constructor,
                                       QScriptValue::ReadOnly|QScriptValue::Undeletable);
    */
}

cllaun::API_Shortcut::~API_Shortcut() {
    delete shortcut_cls;
}


QScriptValue cllaun::API_Shortcut::newShortcutObject(widget::Widget* parent) {
    QScriptEngine* engine = shortcut_cls->engine();
    Shortcuts* shortcuts = new Shortcuts(parent->getQWidget());
    QScriptValue shortcuts_obj = engine->newQObject(shortcuts, QScriptEngine::AutoOwnership);
    QScriptValue instance = engine->newObject(shortcut_cls, shortcuts_obj);

    return instance;
}
