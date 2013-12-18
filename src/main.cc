#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QDebug>

#include "core.h"
#include "config.h"
#include "skin.h"
#include "main_window.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.Engine();
    engine->globalObject().setProperty("global", engine->globalObject());

    // Init Config
    cllaun::Config config;
    config.AddSearchPath(QDir(app.applicationDirPath()));
    config.AddSearchPath(QDir::home());

    // Init Skin
    cllaun::Skin skin(&app);
    skin.AddSearchPath(QDir(app.applicationDirPath() + QDir::separator() + "skins"));

    // 設定ファイルの読み込み
    config.Read("default");
    // スキンの読み込み
    skin.Read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
