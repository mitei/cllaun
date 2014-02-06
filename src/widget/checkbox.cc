#include "checkbox.h"
#include <QScriptEngine>

cllaun::widget::CheckBox::CheckBox(QWidget *parent)
    : AbstractButton(parent)
{
}

QCheckBox* cllaun::widget::CheckBox::getThis() {
    return thisObject().data().toVariant().value<QCheckBox*>();
}


/*
 * Property accessors
 */
bool cllaun::widget::CheckBox::isTristate() {
    return getThis()->isTristate();
}

void cllaun::widget::CheckBox::setTristate(bool y) {
    getThis()->setTristate(y);
}
