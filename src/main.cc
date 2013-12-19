#include <QApplication>
#include <QFile>
#include <QDir>
#include <QMainWindow>

#include "core.h"
#include "config.h"
#include "skin.h"
#include "main_window.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.engine();
    engine->globalObject().setProperty("global", engine->globalObject());

    // Init Config
    cllaun::Config config;
    config.addSearchPath(app.applicationDirPath());
    config.addSearchPath(QDir::homePath());

    // Init Skin
    cllaun::Skin skin(&app);
    skin.addSearchPath(app.applicationDirPath() + QDir::separator() + "skins");

    // 設定ファイルの読み込み
    config.read("default");
    // スキンの読み込み
    skin.read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
