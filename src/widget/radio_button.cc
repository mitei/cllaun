#include "radio_button.h"
#include <QScriptEngine>

cllaun::widget::RadioButton::RadioButton(QWidget *parent)
    : AbstractButton(parent)
{
}

QRadioButton* cllaun::widget::RadioButton::getThis() {
    return thisObject().data().toVariant().value<QRadioButton*>();
}
