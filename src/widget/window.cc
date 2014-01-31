#include "window.h"

cllaun::widget::Window::Window(QWidget* parent)
    : Widget(parent)
{
    self->setWindowFlags(Qt::Window);
}

QString cllaun::widget::Window::getWindowTitle() {
    return self->windowTitle();
}

void cllaun::widget::Window::setWindowTitle(const QString& title) {
    self->setWindowTitle(title);
}

bool cllaun::widget::Window::isFrameless(){
    return (self->windowFlags() & Qt::FramelessWindowHint) ? true : false;
}

void cllaun::widget::Window::setFrameless(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::FramelessWindowHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::FramelessWindowHint);
    }
}

/*
bool cllaun::widget::Window::isNoDropShadow() {
    return (self->windowFlags() & Qt::NoDropShadowWindowHint) ? true : false;
}

void cllaun::widget::Window::setNoDropShadow(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::NoDropShadowWindowHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::NoDropShadowWindowHint);
    }
}
*/

bool cllaun::widget::Window::isStaysOnTop() {
    return (self->windowFlags() & Qt::WindowStaysOnTopHint) ? true : false;
}

void cllaun::widget::Window::setStaysOnTop(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowStaysOnTopHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowStaysOnTopHint);
    }
}

bool cllaun::widget::Window::isStaysOnBottom() {
    return (self->windowFlags() & Qt::WindowStaysOnBottomHint) ? true : false;
}

void cllaun::widget::Window::setStaysOnBottom(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowStaysOnBottomHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowStaysOnBottomHint);
    }
}

/*
bool cllaun::widget::Window::isAcceptFocus() {
    return (self->windowFlags() & Qt::WindowDoesNotAcceptFocus) ? false : true;
}

void cllaun::widget::Window::setAcceptFocus(bool flag) {
    if (!flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowDoesNotAcceptFocus);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowDoesNotAcceptFocus);
    }
}
*/

/*
bool cllaun::widget::Window::hasTitleBar() {
    return (self->windowFlags() & Qt::WindowTitleHint) ? true : false;
}

void cllaun::widget::Window::setHasTitleBar(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowTitleHint);
    } else {
        self->setWindowFlags(self->windowFlags() & (~Qt::WindowTitleHint));
    }
}
*/

bool cllaun::widget::Window::hasMinimizeButton() {
    return (self->windowFlags() & Qt::WindowMinimizeButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasMinimizeButton(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowMinimizeButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowMinimizeButtonHint);
    }
}

bool cllaun::widget::Window::hasMaximizeButton() {
    return (self->windowFlags() & Qt::WindowMaximizeButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasMaximizeButton(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowMaximizeButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowMaximizeButtonHint);
    }
}

bool cllaun::widget::Window::hasCloseButton() {
    return (self->windowFlags() & Qt::WindowCloseButtonHint) ? true : false;
}

void cllaun::widget::Window::setHasCloseButton(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowCloseButtonHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowCloseButtonHint);
    }
}

// for Mac
bool cllaun::widget::Window::hasSystemMenu() {
    return (self->windowFlags() & Qt::WindowSystemMenuHint) ? true : false;
}

void cllaun::widget::Window::setHasSystemMenu(bool flag) {
    if (flag) {
        self->setWindowFlags(self->windowFlags() | Qt::WindowSystemMenuHint);
    } else {
        self->setWindowFlags(self->windowFlags() & ~Qt::WindowSystemMenuHint);
    }
}
