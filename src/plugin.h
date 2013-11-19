#pragma once

#include <QVector>
#include <String>
#include <QScriptEngine>
#include <QLibrary>

namespace cllaun
{
    typedef QVector<QString> PluginArguments;

    // プラグイン機能の初期化
    void InitPlugin(QScriptEngine* engine);
    // プラグイン・コマンドの実行
    void RunPluginCommand(QScriptEngine* engine, const QString& name, PluginArguments& args);
    // ネイティブプラグインのロード
    QLibrary* LoadNativePlugin(QScriptEngine* engine, const QString& path);
    // JavaScript ファイルを実行
    void RunScriptFile(QScriptEngine* engine, const QString& path);
}
