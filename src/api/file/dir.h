#pragma once

#include <QObject>
#include <QDir>
#include <QScriptable>


namespace cllaun {

class DirProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    DirProto(QObject* parent) : QObject(parent) {}

public slots:
    bool cd(const QString& dir_name);
    bool cdUp();
    qint32 count() const;
    QString name() const;
    QString path() const;
    QString filePath(const QString& file_name) const;
    bool exists(const QString& file_name) const;
    bool exists() const;
    bool mkdir(const QString& dir_name) const;
    bool mkpath(const QString& dir_path) const;
    bool rmdir(const QString& dir_name) const;
    bool rmpath(const QString& dir_path) const;
    QStringList entryList(const QStringList& name_filters,
                          QDir::Filters filters = QDir::NoFilter,
                          QDir::SortFlags sort = QDir::NoSort);
    QStringList entryList(QDir::Filters filters = QDir::NoFilter,
                          QDir::SortFlags sort = QDir::NoSort);
};


class Dir : public QObject {
    Q_OBJECT

public:
    Dir(QObject* parent = nullptr) : QObject(parent) {}
    Dir(const QDir& other) : self(other) {}
    Dir(const QString& path, QObject* parent = nullptr) : QObject(parent), self(path) {}

    QDir* getThis() { return &self; }

private:
    QDir self;
};

}
