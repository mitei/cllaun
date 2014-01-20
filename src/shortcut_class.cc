#include "shortcut_class.h"
#include <QScriptEngine>
#include <QShortcut>
#include <QDebug>
#include "widget/widget.h"

Q_DECLARE_METATYPE(QKeySequence)

/*
 * -----
 * Class Shortcut
 * -----
 */
cllaun::Shortcut::Shortcut(QWidget* parent, const QScriptValue& _callback)
    : QObject(parent), shortcut(parent), callback(_callback)
{
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

void cllaun::Shortcut::setKey(const QKeySequence& key) {
    shortcut.setKey(key);
}

QKeySequence cllaun::Shortcut::getKeySequence() const {
    return shortcut.key();
}

const QScriptValue& cllaun::Shortcut::getCallback() const {
    return callback;
}


/*
 * -----
 * Class Shortcuts
 * -----
 */
cllaun::Shortcuts::~Shortcuts() {
    foreach (Shortcut* s, shortcuts) {
        delete s;
    }
}

void cllaun::Shortcuts::setShortcut(const QKeySequence& key, const QScriptValue& callback) {
    Shortcut* shortcut = new Shortcut(parent, callback);
    shortcut->setKey(key);
    shortcuts.push_back(shortcut);
}

cllaun::Shortcut* cllaun::Shortcuts::getShortcut(const QKeySequence& key) {
    foreach (Shortcut* s, shortcuts) {
        if (s->getKeySequence() == key) return s;
    }
    return nullptr;
}

void cllaun::Shortcuts::remove(const QKeySequence& key) {
    for (auto iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        Shortcut* s = (*iter);
        if (s->getKeySequence() == key) {
            delete s;
            shortcuts.erase(iter);
            return;
        }
    }
}


/*
 * -----
 * Class ShortcutClass
 * -----
 */

cllaun::ShortcutClass::ShortcutClass(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
    qScriptRegisterMetaType(engine, keySequenceToScriptValue, keySequenceFromScriptValue);
}

QScriptValue::PropertyFlags cllaun::ShortcutClass::propertyFlags(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    QKeySequence key(name.toString());
    // if `key == ""`, name is invalid key-sequence string.
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
    // if `key == ""`, name is invalid key-sequence string.
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
    Shortcuts* shortcuts = qobject_cast<Shortcuts*>(object.data().toQObject());
    Shortcut* shortcut = shortcuts->getShortcut(QKeySequence(name.toString()));
    if (shortcut == nullptr) {
        return QScriptValue();
    } else {
        return engine()->newQObject(shortcut, QScriptEngine::QtOwnership);
    }
}

void cllaun::ShortcutClass::setProperty(
        QScriptValue& object,
        const QScriptString& name,
        uint id,
        const QScriptValue& value)
{
    if (!value.isNull() && !value.isFunction()) {
        object.engine()->currentContext()
                ->throwError("Argument Error: Right-hand value must be a function or null.");
        return;
    }

    Shortcuts* shortcuts = qobject_cast<Shortcuts*>(object.data().toQObject());
    QKeySequence key(name);
    if (value.isNull()) {
        shortcuts->remove(key);
    } else {
        shortcuts->setShortcut(key, value);
    }
}

/*
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
*/

QScriptValue cllaun::ShortcutClass::keySequenceToScriptValue(
        QScriptEngine *engine, const QKeySequence &keyseq)
{
    return QScriptValue(keyseq.toString());
}

void cllaun::ShortcutClass::keySequenceFromScriptValue(
        const QScriptValue &obj, QKeySequence &keyseq)
{
    keyseq = QKeySequence(obj.toString());
}
