#include "widget/line_edit.h"
#include <QWidget>
#include <QLineEdit>

cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : cllaun::widget::Widget(new QLineEdit, parent)
{
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
}

cllaun::widget::LineEdit::~LineEdit() {
}

QString cllaun::widget::LineEdit::getText() const {
    return dynamic_cast<QLineEdit*>(self)->text();
}

void cllaun::widget::LineEdit::setText(const QString& text) {
    dynamic_cast<QLineEdit*>(self)->setText(text);
}

void cllaun::widget::LineEdit::emitReturnPressed() {
    emit returnPressed();
}

void cllaun::widget::LineEdit::selectAll() {
    dynamic_cast<QLineEdit*>(self)->selectAll();
}
