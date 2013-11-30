#include "config.h"
#include "core.h"
#include "api.h"

#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>

const char* cllaun::Config::extension = ".cllaun_conf";

/*!
 * @brief 指定された設定ファイルを読み込む
 *
 * @param conf_name 設定ファイルの名前（{conf_name}.cllaun_conf）
 */
void cllaun::Config::Read(const QString& conf_name) {
    const QVector<QString> dirs = Core::ConfigDirs();
    QString conf_file_name = conf_name + extension;
    foreach (auto dir_path, dirs) {
        QDir dir(dir_path);
        if (dir.exists(conf_file_name)) {
            RunScriptFile(dir.filePath(conf_file_name));
            break;
        }
    }
}

/*!
 * @brief すべての設定ファイルを読み込む
 */
void cllaun::Config::ReadAll() {
    const QVector<QString> dirs = Core::ConfigDirs();
    QStringList name_filter;
    name_filter << QString("*") + extension;
    QDir::Filter filter = QDir::Files;
    QDir::SortFlag sort_flag = QDir::Name;

    foreach (auto dir_path, dirs) {
        QDir dir(dir_path);
        QStringList conf_list = dir.entryList(name_filter, filter, sort_flag);

        foreach (auto conf_name, conf_list) {
            RunScriptFile(dir.filePath(conf_name));
        }
    }
}
