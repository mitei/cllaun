#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include "main_window.h"
#include "plugin.h"
#include "api_common.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // QSS の設定。暫定
    QFile main_style_file("assets/style.qss");
    main_style_file.open(QFile::ReadOnly);
    QString str_style = QString::fromUtf8(main_style_file.readAll());
    app.setStyleSheet(str_style);

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    cllaun::InitPlugin(&engine);
    cllaun::InitCommon(&engine);

    return app.exec();
}
