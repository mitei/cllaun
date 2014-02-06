#include "abstract_button_proto.h"
#include <QScriptEngine>
#include <QAbstractButton>

QAbstractButton* cllaun::widget::AbstractButtonProto::getThis() {
    return thisObject().data().toVariant().value<QAbstractButton*>();
}

/*
 * Slots
 */

//void cllaun::widget::AbstractButtonProto::animateClick(int msec) {
//}

void cllaun::widget::AbstractButtonProto::click() {
    getThis()->click();
}

void cllaun::widget::AbstractButtonProto::toggle() {
    getThis()->toggle();
}
