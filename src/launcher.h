#pragma once

class QString;

namespace cllaun {

// コマンドを実行
int Run(const QString& command);
// ファイルを開く
int Execute(const QString& path, const QString& args);

}
