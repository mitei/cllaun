#include "global_shortcut_class.h"
#include <QxtWidgets/QxtGlobalShortcut>
#include <QScriptEngine>
#include <QKeySequence>


/*
 * -----
 * Class GlobalShortcut
 * -----
 */
cllaun::GlobalShortcut::GlobalShortcut(QObject* parent, const QScriptValue& _callback)
    : QObject(parent), shortcut(parent), callback(_callback)
{
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

void cllaun::GlobalShortcut::setKey(const QKeySequence& key) {
    shortcut.setShortcut(key);
}

QKeySequence cllaun::GlobalShortcut::getKeySequence() const {
    return shortcut.shortcut();
}

const QScriptValue& cllaun::GlobalShortcut::getCallback() const {
    return callback;
}


/*
 * -----
 * Class GlobalShortcuts
 * -----
 */
cllaun::GlobalShortcuts::~GlobalShortcuts() {
    foreach (GlobalShortcut* s, shortcuts) {
        delete s;
    }
}

void cllaun::GlobalShortcuts::setShortcut(const QKeySequence& key, const QScriptValue& callback) {
    GlobalShortcut* shortcut = new GlobalShortcut(parent, callback);
    shortcut->setKey(key);
    shortcuts.push_back(shortcut);
}

cllaun::GlobalShortcut* cllaun::GlobalShortcuts::getShortcut(const QKeySequence& key) {
    foreach (GlobalShortcut* s, shortcuts) {
        if (s->getKeySequence() == key) return s;
    }
    return nullptr;
}

void cllaun::GlobalShortcuts::remove(const QKeySequence& key) {
    for (auto iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        GlobalShortcut* s = (*iter);
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

cllaun::GlobalShortcutClass::GlobalShortcutClass(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
}

QScriptValue::PropertyFlags cllaun::GlobalShortcutClass::propertyFlags(
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

QScriptClass::QueryFlags cllaun::GlobalShortcutClass::queryProperty(
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

QScriptValue cllaun::GlobalShortcutClass::property(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    GlobalShortcuts* shortcuts = qobject_cast<GlobalShortcuts*>(object.data().toQObject());
    GlobalShortcut* shortcut = shortcuts->getShortcut(QKeySequence(name.toString()));
    if (shortcut == nullptr) {
        return QScriptValue();
    } else {
        return engine()->newQObject(shortcut, QScriptEngine::QtOwnership);
    }
}

void cllaun::GlobalShortcutClass::setProperty(
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

    GlobalShortcuts* shortcuts = qobject_cast<GlobalShortcuts*>(object.data().toQObject());
    QKeySequence key(name);
    if (value.isNull()) {
        shortcuts->remove(key);
    } else {
        shortcuts->setShortcut(key, value);
    }
}
