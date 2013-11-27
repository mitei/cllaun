#pragma once

#include <QVector>
#include <QString>
#include <QLibrary>

namespace cllaun {

typedef QVector<QString> PluginArguments;

// プラグイン機能の初期化
void InitPlugin();
// プラグイン・コマンドの実行
void RunPluginCommand(const QString& name, PluginArguments& args);
// ネイティブプラグインのロード
QLibrary* LoadNativePlugin(const QString& path);
// JavaScript ファイルを実行
void RunScriptFile(const QString& path);

}
