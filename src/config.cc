#include "config.h"
#include "plugin.h"
#include "core.h"

#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>

const char* cllaun::Config::suffix = ".cllaun_conf";

void cllaun::Config::Read(const QString& conf_name) {
    const QVector<QString> dirs = Core::ConfigDirs();
    QString conf_file_name = conf_name + suffix;
    for (auto iter = dirs.begin(); iter != dirs.end(); ++iter) {
        QDir dir(*iter);
        if (dir.exists(conf_file_name)) {
            RunScriptFile(dir.filePath(conf_file_name));
            break;
        }
    }
}
