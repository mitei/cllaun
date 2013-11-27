#include "core.h"
#include <QCoreApplication>
#include <QDir>

cllaun::Core* cllaun::Core::self = nullptr;

cllaun::Core::Core() {
    self = this;

    plugin_dirs.append(QCoreApplication::applicationDirPath() + QDir::separator() + "plugins");
    skin_dirs.append(QCoreApplication::applicationDirPath() + QDir::separator() + "skins");
}

cllaun::Core::~Core() {
    self = nullptr;
}
