#include "line_edit_proto.h"
#include <QScriptEngine>
#include <QLineEdit>

QLineEdit* cllaun::widget::LineEditProto::getThis() {
    return thisObject().data().toVariant().value<QLineEdit*>();
}

void cllaun::widget::LineEditProto::setSelection(int start, int length) {
    getThis()->setSelection(start, length);
}

void cllaun::widget::LineEditProto::home(bool mark) {
    getThis()->home(mark);
}

void cllaun::widget::LineEditProto::end(bool mark) {
    getThis()->end(mark);
}

void cllaun::widget::LineEditProto::deselect() {
    getThis()->deselect();
}

void cllaun::widget::LineEditProto::selectAll() {
    getThis()->selectAll();
}

void cllaun::widget::LineEditProto::clear() {
    getThis()->clear();
}

void cllaun::widget::LineEditProto::copy() {
    getThis()->copy();
}
void cllaun::widget::LineEditProto::cut() {
    getThis()->cut();
}

void cllaun::widget::LineEditProto::paste() {
    getThis()->paste();
}

void cllaun::widget::LineEditProto::redo() {
    getThis()->redo();
}

void cllaun::widget::LineEditProto::undo() {
    getThis()->undo();
}

