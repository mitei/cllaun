#include "skin.h"
#include "core.h"
#include "api.h"

#include <QApplication>
#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>

#include <QDebug>

void cllaun::Skin::Read(const QString& name) {
    QVector<QString> dirs = Core::SkinDirs();

    foreach (auto dir_path, dirs) {
        QDir dir(dir_path + QDir::separator() + name);
        qDebug() << "Skin::Read() :" << dir.absolutePath();
        if (dir.exists() && dir.exists("style.qss")) {
            QFile style_file(dir.filePath("style.qss"));
            style_file.open(QFile::ReadOnly);
            QString str_style = QString::fromUtf8(style_file.readAll());
            style_file.close();
            Core::App()->setStyleSheet(str_style);
        }
    }
}
