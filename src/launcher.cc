#include <QCoreApplication>
#include <QProcess>
#include <QString>
#include <QDebug>

#include "launcher.h"

int cllaun::Run(const QString& command) {
    qDebug() << "cllaun::Run():" << command;

    if (command == "exit") {
        QCoreApplication::exit(0);
        return 0;
    }
    return QProcess::execute(command);
}
