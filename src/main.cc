#include <QApplication>
#include <QMainWindow>
#include <QFile>
#include "main_window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QMainWindow main_w;

    QFile main_style_file("assets/style.qss");
    main_style_file.open(QFile::ReadOnly);
    QString str_style = QString::fromUtf8(main_style_file.readAll());
    app.setStyleSheet(str_style);

    cllaun::MainWindow mymain_w(&main_w);
    mymain_w.move(400, 300);
    mymain_w.show();

    return app.exec();
}
