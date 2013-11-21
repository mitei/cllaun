#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include "debug.h"
#include "plugin.h"
#include "api_common.h"

int main(int argc, char** argv) {
    using namespace cllaun;

    QCoreApplication app(argc, argv);

    // スクリプトエンジンの初期化
    QScriptEngine engine;
    InitDebug(&engine);
    InitPlugin(&engine);
    InitCommon(&engine);

    QFileInfo f("F:/Projects/qt/cllaun/test/src/plugin_test.js");
    qDebug() << QDir::currentPath();
    qDebug() << (f.exists() ? "src/plugin_test.js exists." : "");
    RunScriptFile(&engine, "F:/Projects/qt/cllaun/test/src/plugin_test.js");

    return app.exec();
}
