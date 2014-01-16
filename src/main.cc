#include <QApplication>
#include <QScriptEngine>

#include "api/api_config.h"
#include "api/api_skin.h"
#include "api/api_widgets.h"
#include "api/api_common.h"
#include "api/api_console.h"
#include "api/api_shortcut.h"
#include "api/api_parser.h"
#include "api/api_launcher.h"


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
    cllaun::API_Shortcut   api_shortcut(&engine);
    cllaun::API_Parser     api_parser(&engine);
    cllaun::API_Launcher   api_launcher(&engine);

    // 設定ファイルの読み込み
    engine.evaluate("config.read();");

    return app.exec();
}
