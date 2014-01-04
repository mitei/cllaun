#include "command.h"

const QString cllaun::Command::getType() const {
    switch (this->type) {
    case INVALID:
        return QString("invalid");
    case EXECUTABLE:
        return QString("executable");
    case PLUGIN:
        return QString("plugin");
    case PATH:
        return QString("path");
    case ALIAS:
        return QString("alias");
    case ANY:
        return QString("any");
    default:
        return QString("invalid");
    }
}
