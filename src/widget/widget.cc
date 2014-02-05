#include "widget/widget.h"
#include "widget/widget_proto.h"
#include <QEvent>


cllaun::widget::Widget::Widget(QWidget* parent)
    : QObject(parent)
{
}

cllaun::widget::Widget::~Widget() {
}

void cllaun::widget::Widget::initialize(QWidget* self) {
    self->installEventFilter(this);
}

QWidget* cllaun::widget::Widget::getThis() {
    return thisObject().data().toVariant().value<QWidget*>();
}

bool cllaun::widget::Widget::eventFilter(QObject* obj, QEvent* event) {
    switch (event->type()) {
    case QEvent::ShortcutOverride:
        return true;
    default:
        return false;
    }
}

/*
 * Property accessors
 */

int cllaun::widget::Widget::x() {
    return getThis()->x();
}

void cllaun::widget::Widget::setX(int _x) {
    QWidget* self = getThis();
    self->move(_x, self->y());
}

int cllaun::widget::Widget::y() {
    return getThis()->y();
}

void cllaun::widget::Widget::setY(int _y) {
    QWidget* self = getThis();
    self->move(self->x(), _y);
}

int cllaun::widget::Widget::width() {
    return getThis()->width();
}

void cllaun::widget::Widget::setWidth(int w) {
    QWidget* self = getThis();
    self->resize(w, self->height());
}

int cllaun::widget::Widget::height() {
    return getThis()->height();
}

void cllaun::widget::Widget::setHeight(int h) {
    QWidget* self = getThis();
    self->resize(self->width(), h);
}

QString cllaun::widget::Widget::tooltip() {
    return getThis()->toolTip();
}

void cllaun::widget::Widget::setTooltip(const QString& t) {
    getThis()->setToolTip(t);
}

QString cllaun::widget::Widget::styleSheet() {
    return getThis()->styleSheet();
}

void cllaun::widget::Widget::setStyleSheet(const QString& s) {
    getThis()->setStyleSheet(s);
}

QString cllaun::widget::Widget::id() {
    return getThis()->objectName();
}

void cllaun::widget::Widget::setId(const QString& i) {
    getThis()->setObjectName(i);
}

bool cllaun::widget::Widget::isTranslucentBackground() {
    return getThis()->testAttribute(Qt::WA_TranslucentBackground);
}

void cllaun::widget::Widget::setTranslucentBackground(bool on) {
    getThis()->setAttribute(Qt::WA_TranslucentBackground, on);
}
