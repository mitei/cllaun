#include <QApplication>
#include <QScriptEngine>
#include <QFileInfo>
#include <QStringList>
#include <QDir>
#include "api/api_skin.h"
#include "api/api_plugin.h"
#include "api/api_widgets.h"
#include "api/api_common.h"
#include "api/api_sys.h"
#include "api/api_console.h"
#include "api/api_parser.h"
#include "api/api_launcher.h"
#include "api.h"

#define VERSION "0.0.0"
#define APP_NAME "Cllaun"


int main(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationVersion(VERSION);
    app.setApplicationName(APP_NAME);
    app.setQuitOnLastWindowClosed(false);
    app.addLibraryPath(app.applicationDirPath() + "/plugins");

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    engine.globalObject().setProperty("global", engine.globalObject());
    cllaun::API_Skin       api_skin(&engine, &app);
    cllaun::API_Widgets    api_widgets(&engine);
    cllaun::API_Common     api_common(&engine);
    cllaun::API_Sys        api_sys(&engine);
    cllaun::API_Console    api_console(&engine);
    cllaun::API_Parser     api_parser(&engine);
    cllaun::API_Launcher   api_launcher(&engine);
    cllaun::API_Plugin     api_plugin(&engine);

    // 設定ファイルの読み込み
    QStringList conflist = QStringList() << (app.applicationDirPath() + "/.cllaun")
                                         << (app.applicationDirPath() + "/_cllaun")
                                         << (QDir::homePath() + "/.cllaun")
                                         << (QDir::homePath() + "/_cllaun");
    foreach (const QString conf, conflist) {
        QFileInfo confinfo(conf);
        if (confinfo.exists()) {
            if (!cllaun::runScriptFile(&engine, conf)) return 1;
        }
    }

    return app.exec();
}
