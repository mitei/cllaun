#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QDebug>

#include "core.h"
#include "config.h"
#include "plugin.h"
#include "skin.h"
#include "main_window.h"

#include "api_common.h"
#include "api_file.h"

// for JavaScript-Test
QScriptValue Print(QScriptContext* context, QScriptEngine* engine) {
    for (int i = 0; i < context->argumentCount(); i++) {
        qDebug() << context->argument(i).toString();
    }
    return QScriptValue::UndefinedValue;
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.Engine();
    engine->globalObject().setProperty("global", engine->globalObject());
    // Test用
    engine->globalObject().setProperty("print", engine->newFunction(Print));
    cllaun::InitCommon();
    cllaun::InitFile();

    // Init Config
    cllaun::Config config;
    config.AddSearchPath(QDir(app.applicationDirPath()));
    config.AddSearchPath(QDir::home());

    // Init Plugin
    cllaun::Plugin plugin;
    plugin.AddSearchPath(QDir(app.applicationDirPath() + QDir::separator() + "plugins"));

    // Init Skin
    cllaun::Skin skin(&app);
    skin.AddSearchPath(QDir(app.applicationDirPath() + QDir::separator() + "skins"));

    // read config
    config.Read("default");
    // read plugin
    plugin.ReadAll();
    // read skin
    skin.Read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return app.exec();
}
