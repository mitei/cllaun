#include <QApplication>
#include <QScriptEngine>
#include <QFile>
#include <QDir>
#include <QMainWindow>

#include "api_config.h"
#include "api_skin.h"
#include "main_window.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    engine.globalObject().setProperty("global", engine.globalObject());
    cllaun::initConfig(&engine);
    cllaun::initSkin(&engine, &app);

    // 設定ファイルの読み込み
    engine.evaluate("config.read('default');");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
