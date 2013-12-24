#include <QApplication>
#include <QScriptEngine>
//#include <QFile>
//#include <QDir>
//#include <QMainWindow>

#include "api_config.h"
#include "api_skin.h"
#include "api_widgets.h"
//#include "main_window.h"


#include <stdlib.h>

QScriptValue exitFunc(QScriptContext* context, QScriptEngine* engine) {
    exit(0);
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    engine.globalObject().setProperty("global", engine.globalObject());
    cllaun::API_Config api_config(&engine);
    cllaun::API_Skin api_skin(&engine, &app);
    cllaun::API_Widgets api_widgets(&engine);
    engine.globalObject().setProperty("exit", engine.newFunction(exitFunc));

    // 設定ファイルの読み込み
    engine.evaluate(
                "config.read('default');"
    );

    // メインウィンドウ
    //QMainWindow main_window;
    //cllaun::MainWindow mymain_window(&main_window);
    //cllaun::MainWindow mymain_window;
    //mymain_window.move(400, 300);
    //mymain_window.show();

    return app.exec();
}
