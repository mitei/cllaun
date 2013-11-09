#include "launcher.h"
#include "common.h"

#include <QProcess>
#include <QDebug>

int cllaun::Run(const QString& command) {
    qDebug() << "cllaun::Run():" << command;

    if (command == "exit") {
        cllaun::Exit(0);
        return 0;
    }
    return QProcess::execute(command);
}
