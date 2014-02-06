#include "abstract_button.h"
#include <QAbstractButton>

cllaun::widget::AbstractButton::AbstractButton(QWidget *parent)
    : Widget(parent)
{
}

void cllaun::widget::AbstractButton::initialize(QWidget *self) {
    QAbstractButton* self_b = dynamic_cast<QAbstractButton*>(self);

    connect(self_b, SIGNAL(toggled(bool)),
            this, SLOT(emitToggled(bool)));
    connect(self_b, SIGNAL(clicked(bool)),
            this, SLOT(emitClicked(bool)));
    connect(self_b, SIGNAL(pressed()),
            this, SLOT(emitPressed()));
    connect(self_b, SIGNAL(released()),
            this, SLOT(emitReleased()));
}

QAbstractButton* cllaun::widget::AbstractButton::getThis() {
    return thisObject().data().toVariant().value<QAbstractButton*>();
}


/*
 * Property accessors
 */

QString cllaun::widget::AbstractButton::text() {
    return getThis()->text();
}

void cllaun::widget::AbstractButton::setText(const QString& t) {
    getThis()->setText(t);
}

//bool cllaun::widget::AbstractButton::autoExclusive() {
//}

//void cllaun::widget::AbstractButton::setAutoExclusive(bool) {
//}

//bool cllaun::widget::AbstractButton::autoRepeat() {
//}

//void cllaun::widget::AbstractButton::setAutoRepeat(bool) {
//}

bool cllaun::widget::AbstractButton::checkable() {
    return getThis()->isCheckable();
}

void cllaun::widget::AbstractButton::setCheckable(bool c) {
    getThis()->setCheckable(c);
}

bool cllaun::widget::AbstractButton::checked() {
    return getThis()->isChecked();
}

void cllaun::widget::AbstractButton::setChecked(bool c) {
    getThis()->setChecked(c);
}

//int cllaun::widget::AbstractButton::autoRepeatDelay() {
//}

//void cllaun::widget::AbstractButton::setAutoRepeatDelay(int) {
//}

//int cllaun::widget::AbstractButton::autoRepeatInterval() {
//}

//void cllaun::widget::AbstractButton::setAutoRepeatInterval(int) {
//}

//QIcon cllaun::widget::AbstractButton::icon() {
//}

//void cllaun::widget::AbstractButton::setIcon(const QIcon&) {
//}

//QSize cllaun::widget::AbstractButton::iconSize() {
//}

//void cllaun::widget::AbstractButton::setIconSize(const QSize&) {
//}

bool cllaun::widget::AbstractButton::down() {
    return getThis()->isDown();
}

void cllaun::widget::AbstractButton::setDown(bool d) {
    getThis()->setDown(d);
}

