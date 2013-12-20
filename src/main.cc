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
    cllaun::Config* config = new cllaun::Config;
    config->dirs() << app.applicationDirPath()
                  << QDir::homePath();

    // Init Skin
    cllaun::Skin* skin = new cllaun::Skin(&app);
    skin->dirs() << app.applicationDirPath() + "/skins";

    QScriptValue config_obj = engine->newQObject(config, QScriptEngine::AutoOwnership);
    QScriptValue skin_obj = engine->newQObject(skin, QScriptEngine::AutoOwnership);
    engine->globalObject().setProperty("config", config_obj);
    engine->globalObject().setProperty("skin", skin_obj);

    // 設定ファイルの読み込み
    config->read("default");
    // スキンの読み込み
    //skin.read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
