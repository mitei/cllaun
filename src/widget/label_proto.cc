#include "widget/label_proto.h"
#include <QScriptEngine>
#include <QLabel>

QLabel* cllaun::widget::LabelProto::getThis() {
    return thisObject().data().toVariant().value<QLabel*>();
}
