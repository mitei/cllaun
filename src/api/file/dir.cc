#include "api/file/dir.h"
#include <QScriptEngine>

bool cllaun::DirProto::cd(const QString& dir_name) {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->cd(dir_name);
}

bool cllaun::DirProto::cdUp() {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->cdUp();
}

qint32 cllaun::DirProto::count() const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return static_cast<qint32>(self->count());
}
QString cllaun::DirProto::name() const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->dirName();
}
QString cllaun::DirProto::path() const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->path();
}
QString cllaun::DirProto::filePath(const QString& file_name) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->filePath(file_name);
}
bool cllaun::DirProto::exists(const QString& file_name) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->exists(file_name);
}
bool cllaun::DirProto::exists() const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->exists();
}
bool cllaun::DirProto::mkdir(const QString& dir_name) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->mkdir(dir_name);
}
bool cllaun::DirProto::mkpath(const QString& dir_path) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->mkpath(dir_path);
}
bool cllaun::DirProto::rmdir(const QString& dir_name) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->rmdir(dir_name);
}
bool cllaun::DirProto::rmpath(const QString& dir_path) const {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->rmpath(dir_path);
}
QStringList cllaun::DirProto::entryList(const QStringList& name_filters, QDir::Filters filters, QDir::SortFlags sort) {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->entryList(name_filters, filters, sort);
}

QStringList cllaun::DirProto::entryList(QDir::Filters filters, QDir::SortFlags sort) {
    QDir* self = qscriptvalue_cast<Dir*>(thisObject())->getThis();
    return self->entryList(filters, sort);
}
