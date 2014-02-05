#include "widget_proto.h"
#include <QScriptEngine>
#include <QScriptValue>
#include <QWidget>


QWidget* cllaun::widget::WidgetProto::getThis() {
    return thisObject().data().toVariant().value<QWidget*>();
}

void cllaun::widget::WidgetProto::move(int x, int y) {
    getThis()->move(x, y);
}

void cllaun::widget::WidgetProto::resize(int w, int h) {
    getThis()->resize(w, h);
}

void cllaun::widget::WidgetProto::show() {
    getThis()->show();
}

void cllaun::widget::WidgetProto::hide() {
    getThis()->hide();
}

void cllaun::widget::WidgetProto::close() {
    getThis()->close();
}

void cllaun::widget::WidgetProto::setFocus() {
    getThis()->setFocus();
}
