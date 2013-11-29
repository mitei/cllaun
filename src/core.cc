#include "core.h"
#include <QCoreApplication>
#include <QDir>

cllaun::Core* cllaun::Core::self = nullptr;

cllaun::Core::Core() {
    if (self != nullptr) self->~Core();
    self = this;

    plugin_dirs.append(QCoreApplication::applicationDirPath() + QDir::separator() + "plugins");
    skin_dirs.append(QCoreApplication::applicationDirPath() + QDir::separator() + "skins");
    config_dirs.append(QCoreApplication::applicationDirPath());
    config_dirs.append(QDir::homePath());
}

cllaun::Core::~Core() {
    self = nullptr;
}

bool cllaun::Core::AppendPluginDirs(const QString& path) {
    QDir dir(path);
    if (dir.exists()) {
        self->plugin_dirs.append(path);
        return true;
    }
    return false;
}
bool cllaun::Core::AppendSkinDirs(const QString& path) {
    QDir dir(path);
    if (dir.exists()) {
        self->skin_dirs.append(path);
        return true;
    }
    return false;
}
