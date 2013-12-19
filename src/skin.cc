#include "skin.h"

#include <QString>
#include <QDir>
#include <QFile>
#include <QApplication>

#include "dirs.h"


/*!
 * @brief スキン本体の QSS ファイルの名前
 */
const char* cllaun::Skin::skin_file_name = "style.qss";

cllaun::Skin::Skin(QApplication* _app, QObject* parent): QObject(parent), app(_app) { }

/*!
 * @brief 指定されたスキンを読み込む
 *
 * @param name スキン名
 */
void cllaun::Skin::read(const QString& name) {
    const Dirs search_dirs(search_paths);
    const QString skin_dir_path = search_dirs.dirPath(name);
    if (!skin_dir_path.isEmpty()) {
        QDir skin_dir(skin_dir_path);
        if (skin_dir.exists(skin_file_name)) {
            QFile style_file(skin_dir.filePath(skin_file_name));
            style_file.open(QFile::ReadOnly);
            QString str_style = QString::fromUtf8(style_file.readAll());
            style_file.close();
            app->setStyleSheet(str_style);
        }
    }
}

QStringList& cllaun::Skin::dirs() {
    return search_paths;
}

void cllaun::Skin::setDirs(const QStringList &paths) {
    search_paths = paths;
}
