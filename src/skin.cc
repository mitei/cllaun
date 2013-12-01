#include <QVector>
#include <QString>
#include <QDir>
#include <QFile>

#include "core.h"

#include "skin.h"

/*!
 * @brief スキン本体の QSS ファイルの名前
 */
const char* cllaun::Skin::skin_file_name = "style.qss";

/*!
 * @brief 指定されたスキンを読み込む
 *
 * @param name スキン名
 */
void cllaun::Skin::Read(const QString& name) {
    const Dirs dirs = Core::SkinDirs();

    const QString skin_dir_path = dirs.DirPath(name);
    if (!skin_dir_path.isEmpty()) {
        QDir skin_dir(skin_dir_path);
        if (skin_dir.exists(skin_file_name)) {
            QFile style_file(skin_dir.filePath(skin_file_name));
            style_file.open(QFile::ReadOnly);
            QString str_style = QString::fromUtf8(style_file.readAll());
            style_file.close();
            Core::App()->setStyleSheet(str_style);
        }
    }
}
