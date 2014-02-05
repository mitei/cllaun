#include "widget/line_edit.h"
#include <QWidget>

/*!
 * @brief コンストラクタ
 *
 * @param tarent 親ウィジェット
 */
cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : Widget(parent)
{
}

void cllaun::widget::LineEdit::initialize(QWidget* self) {
    QLineEdit* self_l = dynamic_cast<QLineEdit*>(self);
    connect(self_l, SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
    connect(self_l, SIGNAL(cursorPositionChanged(int,int)),
            this, SLOT(emitCursorPositionChanged(int,int)));
    connect(self_l, SIGNAL(editingFinished()),
            this, SLOT(emitEditingFinished()));
    connect(self_l, SIGNAL(selectionChanged()),
            this, SLOT(emitSelectionChanged()));
    connect(self_l, SIGNAL(textChanged(QString)),
            this, SLOT(emitTextChanged(QString)));
    connect(self_l, SIGNAL(textEdited(QString)),
            this, SLOT(emitTextEdited(QString)));
}

QLineEdit* cllaun::widget::LineEdit::getThis() {
    return thisObject().data().toVariant().value<QLineEdit*>();
}

/*
 * ラッパ
 */
QString cllaun::widget::LineEdit::getText() {
    return getThis()->text();
}

void cllaun::widget::LineEdit::setText(const QString& text) {
    getThis()->setText(text);
}

int cllaun::widget::LineEdit::getCursorPosition() {
    return getThis()->cursorPosition();
}

void cllaun::widget::LineEdit::setCursorPosition(int pos) {
    getThis()->setCursorPosition(pos);
}

QString cllaun::widget::LineEdit::getSelectedText() {
    return getThis()->selectedText();
}

int cllaun::widget::LineEdit::getMaxLength() {
    return getThis()->maxLength();
}

void cllaun::widget::LineEdit::setMaxLength(int length) {
    getThis()->setMaxLength(length);
}
