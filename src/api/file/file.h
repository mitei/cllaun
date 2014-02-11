#pragma once

#include <QObject>
#include <QFile>
#include <QScriptable>

namespace cllaun {

class FileProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    FileProto(QObject* parent) : QObject(parent) {}

public slots:
    bool copy(const QString& new_path);
    bool exists() const;
    bool link(const QString& link_path);
    bool remove();
    bool rename(const QString& new_path);
    void setFileName(const QString& name);
};

}
