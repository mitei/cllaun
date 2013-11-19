#include "launcher.h"

#include <QProcess>
#include <QCoreApplication>
#include <QDebug>

int cllaun::Run(const QString& command) {
    qDebug() << "cllaun::Run():" << command;

    if (command == "exit") {
        QCoreApplication::exit(0);
        return 0;
    }
    return QProcess::execute(command);
}
