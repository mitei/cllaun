#include "launcher.h"
#include "common.h"

#include <QProcess>

int cllaun::Run(const QString& command) {
    if (command == "exit") {
        cllaun::Exit(0);
        return 0;
    }
    return QProcess::execute(command);
}
