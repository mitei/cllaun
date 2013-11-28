#include "config.h"
#include "core.h"
#include "api.h"

#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>

const char* cllaun::Config::extension = ".cllaun_conf";

void cllaun::Config::Read(const QString& conf_name) {
    const QVector<QString> dirs = Core::ConfigDirs();
    QString conf_file_name = conf_name + extension;
    for (auto iter = dirs.begin(); iter != dirs.end(); ++iter) {
        QDir dir(*iter);
        if (dir.exists(conf_file_name)) {
            RunScriptFile(dir.filePath(conf_file_name));
            break;
        }
    }
}

void cllaun::Config::ReadAll() {
    const QVector<QString> dirs = Core::ConfigDirs();
    QStringList name_filter;
    name_filter << QString("*") + extension;
    QDir::Filter filter = QDir::Files;
    QDir::SortFlag sort_flag = QDir::Name;

    for (auto iter = dirs.begin(); iter != dirs.end(); ++iter) {
        QDir dir(*iter);
        QStringList conf_list = dir.entryList(name_filter, filter, sort_flag);

        for (auto iter2 = conf_list.begin(); iter2 != conf_list.end(); ++iter2) {
            RunScriptFile(dir.filePath(*iter2));
        }
    }
}
