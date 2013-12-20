#include <QApplication>
#include <QFile>
#include <QDir>
#include <QMainWindow>

#include "core.h"
#include "api_config.h"
#include "api_skin.h"
#include "main_window.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.engine();
    engine->globalObject().setProperty("global", engine->globalObject());
    cllaun::initConfig();
    cllaun::initSkin(&app);

    // 設定ファイルの読み込み
    engine->evaluate("config.read('default');");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
