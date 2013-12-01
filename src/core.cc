#include "core.h"
#include <QCoreApplication>
#include <QDir>

cllaun::Core* cllaun::Core::self = nullptr;

cllaun::Core::Core(int argc, char** argv): app(argc, argv) {
    if (self != nullptr) self->~Core();
    self = this;

    plugin_dirs.append(QDir(QCoreApplication::applicationDirPath() + QDir::separator() + "plugins"));
    skin_dirs.append(QDir(QCoreApplication::applicationDirPath() + QDir::separator() + "skins"));
    config_dirs.append(QDir(QCoreApplication::applicationDirPath()));
    config_dirs.append(QDir::homePath());
}

cllaun::Core::~Core() {
    self = nullptr;
}
