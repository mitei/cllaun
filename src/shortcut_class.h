#pragma once

#include <QObject>
#include <QWidget>
#include <QScriptClass>
#include <QScriptValue>
#include <QVector>

class QScriptEngine;
class QScriptContext;
class QShortcut;

namespace cllaun {

class Shortcuts : public QObject {
    Q_OBJECT

public:
    Shortcuts(QWidget* _parent)
        : QObject(_parent), parent(_parent) { }
    ~Shortcuts();

    void newShortcut(const QString& key, const QScriptValue& callback);

private:
    QVector<QShortcut*> shortcuts;
    QWidget* parent;
};

class ShortcutClass : public QObject, public QScriptClass {
public:
    ShortcutClass(QScriptEngine* engine);

    static QScriptValue constructorFunc(QScriptContext* context, QScriptEngine* engine, void* cls);

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
};

}
