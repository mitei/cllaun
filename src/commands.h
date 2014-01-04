#pragma once

#include <QHash>
#include <QString>
#include <QScriptValue>

namespace cllaun {

class Commands {
public:
    Commands();
    ~Commands();

    bool exists(const QString& name);

private:
    QHash<QString, QScriptValue> commands;
};

}
