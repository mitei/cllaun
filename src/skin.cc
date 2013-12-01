#include "skin.h"
#include "core.h"
#include "api.h"

#include <QApplication>
#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>

const char* cllaun::Skin::skin_file_name = "style.qss";

void cllaun::Skin::Read(const QString& name) {
    const QVector<QDir> dirs = Core::SkinDirs();

    foreach (auto dir, dirs) {
        if (dir.cd(name) && dir.exists(skin_file_name)) {
            QFile style_file(dir.filePath(skin_file_name));
            style_file.open(QFile::ReadOnly);
            QString str_style = QString::fromUtf8(style_file.readAll());
            style_file.close();
            Core::App()->setStyleSheet(str_style);
        }
    }
}
