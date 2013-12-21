#include "config.h"

#include "dirs.h"
#include "api.h"


/*!
 * @brief 設定ファイルの拡張子
 */
const char* cllaun::Config::extension = ".cllaun_conf";

cllaun::Config::Config(QScriptEngine* _engine, QObject *parent)
    : engine(_engine), QObject(parent) {
}

QStringList& cllaun::Config::dirs() {
    return search_paths;
}
void cllaun::Config::setdirs(const QStringList& dirs) {
    search_paths = dirs;
}

/*!
 * @brief 指定された設定ファイルを読み込む
 *
 * @param conf_name 設定ファイルの名前（{conf_name}.cllaun_conf）
 */
void cllaun::Config::read(const QString& conf_name) {
    const Dirs search_dirs(search_paths);
    const QString conf_file_path = search_dirs.filePath(conf_name + extension);
    if (!conf_file_path.isEmpty()) {
        runScriptFile(engine, conf_file_path);
    }
}
