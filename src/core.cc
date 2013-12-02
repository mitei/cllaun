#include <QCoreApplication>
#include <QDir>

#include "core.h"

/*!
 * @brief static-member-function から扱うために必要。cllaun::Core のインスタンスへのポインタ
 */
cllaun::Core* cllaun::Core::self = nullptr;

/*!
 * @brief cllaun の初期化などを行う
 *
 * @param argc QApplication の初期化に必要。
 * @param argv QApplication の初期化に必要。
 */
cllaun::Core::Core(QApplication* _app): app(_app) {
    if (self != nullptr) self->~Core();
    self = this;

    plugin_dirs << (QDir(QCoreApplication::applicationDirPath() + QDir::separator() + "plugins"));
    skin_dirs   << (QDir(QCoreApplication::applicationDirPath() + QDir::separator() + "skins"));
    config_dirs << (QDir(QCoreApplication::applicationDirPath()));
    config_dirs << (QDir(QDir::homePath()));
}

/*!
 * @brief self を初期化
 */
cllaun::Core::~Core() {
    self = nullptr;
}
