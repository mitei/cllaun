#pragma once

#include <QObject>
#include <QWidget>
#include <QScriptClass>
#include <QScriptValue>
#include <QScriptable>
#include <QList>
#include <QShortcut>
#include <QKeySequence>

class QScriptEngine;
class QScriptContext;

namespace cllaun {

/*
 * -----
 * Class Shortcut
 * -----
 */
class Shortcut : public QObject {
    Q_OBJECT
    Q_PROPERTY(QKeySequence key READ getKeySequence)
    Q_PROPERTY(QScriptValue value READ getCallback)

public:
    Shortcut(QWidget* parent, const QScriptValue& _callback);
    void setKey(const QKeySequence& key);
    /* property */
    QKeySequence getKeySequence() const;
    const QScriptValue& getCallback() const;

private:
    QShortcut shortcut;
    QScriptValue callback;
};

/*
 * -----
 * Class Shortcuts
 * -----
 */
class Shortcuts : public QObject {
    Q_OBJECT
public:
    Shortcuts(QWidget* _parent)
        : QObject(_parent), parent(_parent) { }
    ~Shortcuts();

    Shortcut* getShortcut(const QKeySequence& key);
    void setShortcut(const QKeySequence& key, const QScriptValue& callback);
    void remove(const QKeySequence& key);

private:
    QList<Shortcut*> shortcuts;
    QWidget* parent;
};

/*
 * -----
 * Class ShortcutClass
 * -----
 */
class ShortcutClass : public QObject, public QScriptClass {
public:
    ShortcutClass(QScriptEngine* engine);

    //static QScriptValue constructorFunc(QScriptContext* context, QScriptEngine* engine, void* cls);

    QString name() const { return QString("Shortcut"); }

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

private:
    static QScriptValue keySequenceToScriptValue(QScriptEngine* engine, const QKeySequence& keyseq);
    static void keySequenceFromScriptValue(const QScriptValue& obj, QKeySequence& keyseq);
};

}
