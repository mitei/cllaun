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
    cllaun::Core core(argc, argv);

    // スクリプトエンジンの初期化
    QScriptEngine* engine = core.Engine();
    engine->globalObject().setProperty("global", engine->globalObject());
    // Test用
    engine->globalObject().setProperty("print", engine->newFunction(Print));
    cllaun::InitCommon();
    cllaun::InitFile();

    // read config
    cllaun::Config::ReadAll();
    // read plugin
    cllaun::Plugin::Initialize();
    cllaun::Plugin::ReadAll();
    //cllaun::Config::Read("default");
    // read skin
    cllaun::Skin::Read("test_skin");

    // メインウィンドウ
    QMainWindow main_window;
    cllaun::MainWindow mymain_window(&main_window);
    mymain_window.move(400, 300);
    mymain_window.show();

    return core.App()->exec();
}
