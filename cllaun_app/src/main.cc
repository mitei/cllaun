#include <QApplication>
#include <QFile>
#include "main_window.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    QFile main_style_file("assets/style.qss");
    main_style_file.open(QFile::ReadOnly);
    QString str_style = QString::fromUtf8(main_style_file.readAll());
    app.setStyleSheet(str_style);

    cllaun::MainWindow::Instance()->move(400, 300);
    cllaun::MainWindow::Instance()->show();

    return app.exec();
}
