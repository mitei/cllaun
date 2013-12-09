#include "launcher.h"

#include <QCoreApplication>
#include <QProcess>
#include <QString>
#include <QDebug>


/*!
 * @brief コマンドを実行する
 *
 * @param command コマンド文字列
 *
 * @return 実行結果
 */
int cllaun::Run(const QString& command) {
    qDebug() << "cllaun::Run():" << command;

    if (command == "exit") {
        QCoreApplication::exit(0);
        return 0;
    }
    return QProcess::execute(command);
}
