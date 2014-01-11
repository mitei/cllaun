#include <QApplication>
#include <QScriptEngine>

#include "api_config.h"
#include "api_skin.h"
#include "api_widgets.h"
#include "api_common.h"
#include "api_console.h"
#include "api_parser.h"
#include "api_launcher.h"
#include "config.h"


int main(int argc, char** argv) {
    QApplication app(argc, argv);

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    engine.globalObject().setProperty("global", engine.globalObject());
    cllaun::API_Config     api_config(&engine);
    cllaun::API_Skin       api_skin(&engine, &app);
    cllaun::API_Widgets    api_widgets(&engine);
    cllaun::API_Common     api_common(&engine);
    cllaun::API_Console    api_console(&engine);
    cllaun::API_Parser     api_parser(&engine);
    cllaun::API_Launcher   api_launcher(&engine);

    // 設定ファイルの読み込み
    api_config.globalConfig()->read();

    return app.exec();
}
