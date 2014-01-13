#include "widget/widget.h"
#include <QWidget>

cllaun::widget::Widget::Widget(QWidget* _self, QWidget* parent)
    : self(_self)
{
    if (parent != nullptr) {
        self->setParent(parent);
    }
}

cllaun::widget::Widget::~Widget() {
    delete self;
}

QWidget* cllaun::widget::Widget::getQWidget() {
    return self;
}

int cllaun::widget::Widget::getX() const {
    return self->x();
}

void cllaun::widget::Widget::setX(int x) {
    self->move(x, self->y());
}

int cllaun::widget::Widget::getY() const {
    return self->y();
}

void cllaun::widget::Widget::setY(int y) {
    self->move(self->x(), y);
}

int cllaun::widget::Widget::getWidth() const {
    return self->width();
}

void cllaun::widget::Widget::setWidth(int w) {
    self->resize(w, self->height());
}

int cllaun::widget::Widget::getHeight() const {
    return self->height();
}

void cllaun::widget::Widget::setHeight(int h) {
    self->resize(self->width(), h);
}

void cllaun::widget::Widget::move(int x, int y) {
    self->move(x, y);
}

void cllaun::widget::Widget::resize(int w, int h) {
    self->resize(w, h);
}

void cllaun::widget::Widget::show() {
    self->show();
}

void cllaun::widget::Widget::hide() {
    self->hide();
}
