#include "file.h"
#include <QScriptEngine>

bool cllaun::FileProto::copy(const QString& new_path) {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    return self->copy(new_path);
}

bool cllaun::FileProto::exists() const {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    return self->exists();
}

bool cllaun::FileProto::link(const QString& link_path) {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    return self->link(link_path);
}

bool cllaun::FileProto::remove() {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    return self->remove();
}

bool cllaun::FileProto::rename(const QString& new_path) {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    return self->rename(new_path);
}

void cllaun::FileProto::setFileName(const QString& name) {
    QFile* self = qscriptvalue_cast<QFile*>(thisObject().data());
    self->setFileName(name);
}
