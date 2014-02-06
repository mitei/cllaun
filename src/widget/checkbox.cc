#include "checkbox.h"
#include <QScriptEngine>

cllaun::widget::CheckBox::CheckBox(QWidget *parent)
    : AbstractButton(parent)
{
}

void cllaun::widget::CheckBox::initialize(QWidget* self) {
    QCheckBox* self_c = dynamic_cast<QCheckBox*>(self);

    connect(self_c, SIGNAL(stateChanged(int)),
            this, SLOT(emitStateChanged(int)));
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
