#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QMainWindow>
#include "main_window.h"
#include "plugin.h"
#include "api_common.h"
#include "api_file.h"
#include "core.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.Engine();
    engine->globalObject().setProperty("global", engine->globalObject());
    cllaun::InitPlugin();
    cllaun::InitCommon();
    cllaun::InitFile();

    // QSS の設定。暫定
    QFile main_style_file("skins/test_skin/style.qss");
    main_style_file.open(QFile::ReadOnly);
    QString str_style = QString::fromUtf8(main_style_file.readAll());
    main_style_file.close();
    app.setStyleSheet(str_style);

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
