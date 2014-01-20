#pragma once

#include <QObject>
#include <QList>
#include <QScriptClass>
#include <QxtWidgets/QxtGlobalShortcut>

namespace cllaun {
/*
 * -----
 * Class GlobalShortcut
 * -----
 */
class GlobalShortcut : public QObject {
    Q_OBJECT
    Q_PROPERTY(QKeySequence key READ getKeySequence)
    Q_PROPERTY(QScriptValue value READ getCallback)

public:
    GlobalShortcut(QObject* parent, const QScriptValue& _callback);
    void setKey(const QKeySequence& key);
    /* property */
    QKeySequence getKeySequence() const;
    const QScriptValue& getCallback() const;

private:
    QxtGlobalShortcut shortcut;
    QScriptValue callback;
};

/*
 * -----
 * Class GlobalShortcuts
 * -----
 */
class GlobalShortcuts : public QObject {
    Q_OBJECT
public:
    GlobalShortcuts(QObject* _parent)
        : QObject(_parent), parent(_parent) { }
    ~GlobalShortcuts();

    GlobalShortcut* getShortcut(const QKeySequence& key);
    void setShortcut(const QKeySequence& key, const QScriptValue& callback);
    void remove(const QKeySequence& key);

private:
    QList<GlobalShortcut*> shortcuts;
    QObject* parent;
};

/*
 * -----
 * Class GlobalShortcutClass
 * -----
 */
class GlobalShortcutClass : public QObject, public QScriptClass {
public:
    GlobalShortcutClass(QScriptEngine* engine);

    QString name() const { return QString("GlobalShortcut"); }

    QScriptValue::PropertyFlags propertyFlags(const QScriptValue& object,
                                              const QScriptString& name,
                                              uint id);
    QueryFlags queryProperty(const QScriptValue& object,
                               const QScriptString& name,
                               QueryFlags flags,
                               uint* id);
    QScriptValue property(const QScriptValue& object,
                          const QScriptString& name,
                          uint id);
    void setProperty(QScriptValue& object,
                     const QScriptString& name,
                     uint id,
                     const QScriptValue& value);
};

}
