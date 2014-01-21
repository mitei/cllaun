#pragma once

#include <QObject>
#include <QScriptable>
#include <QStringList>
class QScriptEngine;
class QScriptValue;

namespace cllaun {

class Plugin : public QObject, public QScriptable {
    Q_OBJECT
    Q_PROPERTY(QStringList imported READ imported)
    Q_PROPERTY(QStringList available READ available)

public:
    static QScriptValue newQObject(QScriptEngine* engine);
    /* property */
    QStringList imported() const;
    QStringList available() const;

public slots:
    void import(const QString& name) const;
    void importAll() const;

private:
    Plugin(QObject* parent);
};

}
