#include "window.h"

cllaun::widget::Window::Window(QWidget* parent)
    : Widget(parent)
{
}

cllaun::widget::QWindow* cllaun::widget::Window::getThis() {
    return thisObject().data().toVariant().value<QWindow*>();
}

/*
 * Property accessors
 */

QString cllaun::widget::Window::getWindowTitle() {
    return getThis()->windowTitle();
}

void cllaun::widget::Window::setWindowTitle(const QString& title) {
    getThis()->setWindowTitle(title);
}

bool cllaun::widget::Window::isFrameless(){
    return (getThis()->windowFlags() & Qt::FramelessWindowHint) ? true : false;
}

void cllaun::widget::Window::setFrameless(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::FramelessWindowHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::FramelessWindowHint);
    }
}

/*
bool cllaun::widget::Window::isNoDropShadow() {
    return (getThis()->windowFlags() & Qt::NoDropShadowWindowHint) ? true : false;
}

void cllaun::widget::Window::setNoDropShadow(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::NoDropShadowWindowHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::NoDropShadowWindowHint);
    }
}
*/

bool cllaun::widget::Window::isStaysOnTop() {
    return (getThis()->windowFlags() & Qt::WindowStaysOnTopHint) ? true : false;
}

void cllaun::widget::Window::setStaysOnTop(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowStaysOnTopHint);
    }
}

bool cllaun::widget::Window::isStaysOnBottom() {
    return (getThis()->windowFlags() & Qt::WindowStaysOnBottomHint) ? true : false;
}

void cllaun::widget::Window::setStaysOnBottom(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowStaysOnBottomHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowStaysOnBottomHint);
    }
}

/*
bool cllaun::widget::Window::isAcceptFocus() {
    return (getThis()->windowFlags() & Qt::WindowDoesNotAcceptFocus) ? false : true;
}

void cllaun::widget::Window::setAcceptFocus(bool flag) {
    QWindow* self = getThis();
    if (!flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowDoesNotAcceptFocus);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowDoesNotAcceptFocus);
    }
}
*/

/*
bool cllaun::widget::Window::hasTitleBar() {
    return (getThis()->windowFlags() & Qt::WindowTitleHint) ? true : false;
}

void cllaun::widget::Window::setHasTitleBar(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowTitleHint);
    } else {
        self->setWindowFlags(self->windowFlags() & (~Qt::WindowTitleHint));
    }
}
*/

bool cllaun::widget::Window::hasMinimizeButton() {
    return (getThis()->windowFlags() & Qt::WindowMinimizeButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasMinimizeButton(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowMinimizeButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    }
}

bool cllaun::widget::Window::hasMaximizeButton() {
    return (getThis()->windowFlags() & Qt::WindowMaximizeButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasMaximizeButton(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowMaximizeButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    }
}

bool cllaun::widget::Window::hasCloseButton() {
    return (getThis()->windowFlags() & Qt::WindowCloseButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasCloseButton(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowCloseButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowCloseButtonHint);
    }
}

// for Mac
bool cllaun::widget::Window::hasSystemMenu() {
    return (getThis()->windowFlags() & Qt::WindowSystemMenuHint) ? true : false;
}

void cllaun::widget::Window::setHasSystemMenu(bool flag) {
    QWindow* self = getThis();
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowSystemMenuHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowSystemMenuHint);
    }
}
