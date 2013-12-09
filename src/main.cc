#include <QApplication>
#include <QFile>
#include <QMainWindow>
#include <QDebug>

#include "core.h"
#include "config.h"
#include "plugin.h"
#include "skin.h"
#include "main_window.h"

#include "api_plugin.h"
#include "api_common.h"
#include "api_file.h"


// <-- テスト用
QScriptValue Print(QScriptContext* context, QScriptEngine* engine) {
    for (int i = 0; i < context->argumentCount(); i++) {
        qDebug() << context->argument(i).toString();
    }
    return QScriptValue::UndefinedValue;
}
// テスト用 -->

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    cllaun::Core core;

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.Engine();
    engine->globalObject().setProperty("global", engine->globalObject());
    // <-- テスト用
    engine->globalObject().setProperty("print", engine->newFunction(Print));
    //  テスト用 -->
    cllaun::InitPlugin();
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

    // 設定ファイルの読み込み
    config.Read("default");
    // プラグインの読み込み
    plugin.ReadAll();
    // スキンの読み込み
    skin.Read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    engine->evaluate("print(command_line);");

    return app.exec();
}
