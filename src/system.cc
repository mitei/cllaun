#include "system.h"
#include <QApplication>
#include <QProcess>
#include <QDesktopServices>
#include <QUrl>
#include <system.h>


/*!
 * @brief 実行可能ファイルを非同期実行
 *
 * @param path  実行可能ファイルのパス
 * @param args  実行可能ファイルに渡すコマンドライン引数
 *
 * @return      実行に成功したら true
 */
bool cllaun::sys_execute(const QString& path, const QStringList& args) {
    return QProcess::startDetached(path, args);
}

/*!
 * @brief ファイルを開く
 *
 * @param path  ファイルパス
 *
 * @return      ファイルのオープンに成功したら true
 */
bool cllaun::sys_open(const QString& path) {
    return QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

/*!
 * @brief アプリケーションを終了する
 *
 * @param code  終了コード
 */
void cllaun::sys_exit(qint32 code) {
    if (qApp != nullptr) {
        qApp->exit(code);
    } else {
        exit(code);
    }
}
