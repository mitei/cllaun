#include "push_button.h"

cllaun::widget::PushButton::PushButton(QWidget *parent)
    : AbstractButton(parent)
{
}

QPushButton* cllaun::widget::PushButton::getThis() {
    return thisObject().data().toVariant().value<QPushButton*>();
}

//bool cllaun::widget::PushButton::autoDefault() {
//}

//void cllaun::widget::PushButton::setAutoDefault(bool ad) {
//}

//bool cllaun::widget::PushButton::isDefault() {
//}

//void cllaun::widget::PushButton::setDefault(bool d) {
//}

//bool cllaun::widget::PushButton::flat() {
//}

//void cllaun::widget::PushButton::setFlat(bool f) {
//}
