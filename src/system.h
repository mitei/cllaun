#pragma once

#include <QStringList>

namespace cllaun {

// 実行可能ファイルを非同期実行
bool sys_execute(const QString& path, const QStringList& args = QStringList());
// ファイルを開く
bool sys_open(const QString& path);
// アプリケーションを終了する
void sys_exit(qint32 code);

}
