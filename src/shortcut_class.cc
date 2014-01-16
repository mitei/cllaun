#include "shortcut_class.h"
#include <QScriptEngine>
#include <QShortcut>
#include "widget/widget.h"


cllaun::Shortcuts::~Shortcuts() {
}

void cllaun::Shortcuts::newShortcut(
        const QString &key, const QScriptValue& callback) {
    QShortcut* shortcut = new QShortcut(parent);
    shortcut->setKey(QKeySequence(key));
    qScriptConnect(shortcut, SIGNAL(activated()) ,QScriptValue(), callback);
    shortcuts.push_back(shortcut);
}


cllaun::ShortcutClass::ShortcutClass(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
}

QScriptValue::PropertyFlags cllaun::ShortcutClass::propertyFlags(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    QKeySequence key(name.toString());
    // if `key == ""`, name is invalid key-sequence-string.
    if (key.toString() == "") {
        return QScriptValue::SkipInEnumeration;
    }
    return QScriptValue::Undeletable;
}

QScriptClass::QueryFlags cllaun::ShortcutClass::queryProperty(
        const QScriptValue& object,
        const QScriptString& name,
        QueryFlags flags,
        uint* id)
{
    QKeySequence key(name.toString());
    // if `key == ""`, name is invalid key-sequence-string.
    if (key.toString() == "") {
        return 0;
    }
    return flags;
}

QScriptValue cllaun::ShortcutClass::property(
        const QScriptValue &object,
        const QScriptString& name,
        uint id)
{
    // TODO
    return QScriptValue();
}

void cllaun::ShortcutClass::setProperty(
        QScriptValue& object,
        const QScriptString& name,
        uint id,
        const QScriptValue& value)
{
    if (!value.isFunction()) {
        object.engine()->currentContext()->throwError(
                    "Argument Error: Right-hand value must be a function.");
        return;
    }
    Shortcuts* shortcuts = qobject_cast<Shortcuts*>(object.data().toQObject());
    shortcuts->newShortcut(name, value);
}

QScriptValue cllaun::ShortcutClass::constructorFunc(
        QScriptContext* context, QScriptEngine* engine, void* cls)
{
    if (!context->argument(0).isQObject()) {
        context->throwError("Argument Error: argument 0 must be an parent Widget.");
        return QScriptValue();
    }
    widget::Widget* parent_widget = qobject_cast<widget::Widget*>(context->argument(0).toQObject());
    if (parent_widget == nullptr) {
        context->throwError("Argument Error: argument 0 must be an parent Widget.");
        return QScriptValue();
    }
    Shortcuts* shortcuts = new Shortcuts(parent_widget->getQWidget());
    QScriptValue shortcuts_obj = engine->newQObject(shortcuts, QScriptEngine::AutoOwnership);
    QScriptValue instance = engine->newObject(static_cast<ShortcutClass*>(cls), shortcuts_obj);

    return instance;
}
