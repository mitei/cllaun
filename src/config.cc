#include <QVector>
#include <QString>
#include <QStringList>
#include <QDir>

#include "api.h"

#include "config.h"

/*!
 * @brief 設定ファイルの拡張子
 */
const char* cllaun::Config::extension = ".cllaun_conf";

/*!
 * @brief 指定された設定ファイルを読み込む
 *
 * @param conf_name 設定ファイルの名前（{conf_name}.cllaun_conf）
 */
void cllaun::Config::Read(const QString& conf_name) {
    QString conf_file_path = search_paths.FilePath(conf_name + extension);
    if (!conf_file_path.isEmpty()) {
        RunScriptFile(conf_file_path);
    }
}
