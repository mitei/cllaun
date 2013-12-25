#include "api_widgets.h"

#include <QScriptEngine>
#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>

#include "api.h"


cllaun::Widget::Widget(QWidget* _self, QWidget* parent)
    : self(_self)
{
    if (parent != nullptr) {
        self->setParent(parent);
    }
}

cllaun::Widget::~Widget() {
    delete self;
}

QWidget* cllaun::Widget::getQWidget() {
    return self;
}

int cllaun::Widget::getX() {
    return self->x();
}

void cllaun::Widget::setX(int x) {
    self->move(x, self->y());
}

int cllaun::Widget::getY() {
    return self->y();
}

void cllaun::Widget::setY(int y) {
    self->move(self->x(), y);
}

int cllaun::Widget::getWidth() {
    return self->width();
}

void cllaun::Widget::setWidth(int w) {
    self->resize(w, self->height());
}

int cllaun::Widget::getHeight() {
    return self->height();
}

void cllaun::Widget::setHeight(int h) {
    self->resize(self->width(), h);
}

void cllaun::Widget::move(int x, int y) {
    self->move(x, y);
}

void cllaun::Widget::resize(int w, int h) {
    self->resize(w, h);
}

void cllaun::Widget::show() {
    self->show();
}

void cllaun::Widget::hide() {
    self->hide();
}


cllaun::LineEdit::LineEdit(QWidget* parent)
    : cllaun::Widget(new QLineEdit, parent)
{
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
}

cllaun::LineEdit::~LineEdit() {
}

QString cllaun::LineEdit::getText() {
    return dynamic_cast<QLineEdit*>(self)->text();
}

void cllaun::LineEdit::setText(const QString& text) {
    dynamic_cast<QLineEdit*>(self)->setText(text);
}

void cllaun::LineEdit::emitReturnPressed() {
    emit returnPressed();
}

cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : parent_window(new QMainWindow),
      window(new Widget(new QWidget)),
      command_line(new LineEdit)
{
    window->getQWidget()->setParent(parent_window, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    window->getQWidget()->setAttribute(Qt::WA_TranslucentBackground);
    window->getQWidget()->setObjectName("window");
    command_line->getQWidget()->setParent(window->getQWidget());
    command_line->getQWidget()->setObjectName("commandLine");

    engine->globalObject().setProperty("window", engine->newQObject(window));
    engine->globalObject().setProperty("commandLine", engine->newQObject(command_line));
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
}
