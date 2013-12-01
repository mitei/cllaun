#pragma once

#include <QList>
#include <QDir>

class QString;

namespace cllaun {

class Dirs {
public:
    Dirs();
    Dirs(const QList<QDir>& _dirs);

    bool Exists(const QString& name) const;
    QString FilePath(const QString& name) const;
    QString DirPath(const QString& name) const;
    QString Path(const QString& name) const;
    QStringList EntryList(
            const QStringList& name_filters,
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;
    QStringList EntryList(
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;

    void Append(const QDir& value) { dirs << value; }
    Dirs& operator<<(const QDir& value) { dirs << value; return *this; }
private:
    QList<QDir> dirs;
};

}
