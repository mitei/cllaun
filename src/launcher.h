#pragma once

class QString;

namespace cllaun {

// コマンドを実行
int run(const QString& command);
// ファイルを開く
int execute(const QString& path, const QString& args);

}
