#include <QString>
#include <QStringList>

#include "dirs.h"

cllaun::Dirs::Dirs() {
}

cllaun::Dirs::Dirs(const QList<QDir> &_dirs): dirs(_dirs) {
}

bool cllaun::Dirs::Exists(const QString& name) const {
    foreach (QDir dir, dirs) {
        if (dir.exists(name)) return true;
    }
    return false;
}
QString cllaun::Dirs::FilePath(const QString &name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Files|QDir::Hidden;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = EntryList(name_filters, filters, sort_flags);
    return (entry_list.isEmpty() ? QString() : entry_list.at(0) );
}

QString cllaun::Dirs::DirPath(const QString &name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = EntryList(name_filters, filters, sort_flags);
    return (entry_list.isEmpty() ? QString() : entry_list.at(0) );
}

QString cllaun::Dirs::Path(const QString &name) const {
    foreach (QDir dir, dirs) {
        if (dir.exists(name))
            return dir.absolutePath() + QDir::separator() + name;
    }
    return QString();
}

QStringList cllaun::Dirs::EntryList(const QStringList &name_filters, QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (QDir dir, dirs) {
        QStringList entry_list =  dir.entryList(name_filters, filters, sort);
        foreach (QString name, entry_list) {
            all_entry_list << (dir.absolutePath() + QDir::separator() + name);
        }
    }
    return all_entry_list;
}

QStringList cllaun::Dirs::EntryList(QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (QDir dir, dirs) {
        QStringList entry_list =  dir.entryList(filters, sort);
        foreach (QString name, entry_list) {
            all_entry_list << (dir.absolutePath() + QDir::separator() + name);
        }
    }
    return all_entry_list;
}
