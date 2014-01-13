#pragma once

#include <QObject>
#include <QScriptClass>
#include <QScriptValue>

class QScriptEngine;
class QScriptContext;

namespace cllaun {

class Shortcut : public QObject, public QScriptClass {
public:
    Shortcut(QScriptEngine* engine);

    QScriptValue constructor() { return ctor; }



    QString name() const { return QString("Shortcut"); }

    QueryFlags queryProperty(const QScriptValue& object,
                               const QScriptString& name,
                               QueryFlags flags,
                               uint* id);
    QScriptValue property(const QScriptValue &object,
                          const QScriptString& name,
                          uint id);
    void setProperty(QScriptValue& object,
                     const QScriptString& name,
                     uint id,
                     const QScriptValue& value);

private:
    static QScriptValue constructorFunc(QScriptContext* context, QScriptEngine* engine);

private:
    QScriptValue ctor;
};

}
