#include <QCoreApplication>
#include <QDir>

#include "core.h"

/*!
 * @brief cllaun::Core のインスタンスへのポインタ
 */
cllaun::Core* cllaun::Core::self = nullptr;

/*!
 * @brief cllaun の初期化などを行う
 */
cllaun::Core::Core() {
    if (self != nullptr) self->~Core();
    self = this;
}

/*!
 * @brief self を初期化
 */
cllaun::Core::~Core() {
    self = nullptr;
}
