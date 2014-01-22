#include "widget/line_edit.h"
#include <QWidget>
#include <QLineEdit>

/*!
 * @brief コンストラクタ
 *
 * @param tarent 親ウィジェット
 */
cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : cllaun::widget::Widget(new QLineEdit, parent)
{
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(cursorPositionChanged(int,int)),
            this, SLOT(emitCursorPositionChanged(int,int)));
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(editingFinished()),
            this, SLOT(emitEditingFinished()));
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(selectionChanged()),
            this, SLOT(emitSelectionChanged()));
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(textChanged(QString)),
            this, SLOT(emitTextChanged(QString)));
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(textEdited(QString)),
            this, SLOT(emitTextEdited(QString)));
}

/*!
 * @brief デストラクタ
 */
cllaun::widget::LineEdit::~LineEdit() {
}

/*
 * ラッパ
 */
QString cllaun::widget::LineEdit::getText() const {
    return dynamic_cast<QLineEdit*>(self)->text();
}

int cllaun::widget::LineEdit::getCursorPosition() const {
    return dynamic_cast<QLineEdit*>(self)->cursorPosition();
}

void cllaun::widget::LineEdit::setCursorPosition(int pos) {
    dynamic_cast<QLineEdit*>(self)->setCursorPosition(pos);
}

QString cllaun::widget::LineEdit::getSelectedText() const {
    return dynamic_cast<QLineEdit*>(self)->selectedText();
}

int cllaun::widget::LineEdit::getMaxLength() const {
    return dynamic_cast<QLineEdit*>(self)->maxLength();
}

void cllaun::widget::LineEdit::setMaxLength(int length) {
    dynamic_cast<QLineEdit*>(self)->setMaxLength(length);
}

void cllaun::widget::LineEdit::setSelection(int start, int length) {
    dynamic_cast<QLineEdit*>(self)->setSelection(start, length);
}

void cllaun::widget::LineEdit::home(bool mark) {
    dynamic_cast<QLineEdit*>(self)->home(mark);
}

void cllaun::widget::LineEdit::end(bool mark) {
    dynamic_cast<QLineEdit*>(self)->end(mark);
}

void cllaun::widget::LineEdit::deselect() {
    dynamic_cast<QLineEdit*>(self)->deselect();
}

void cllaun::widget::LineEdit::setText(const QString& text) {
    dynamic_cast<QLineEdit*>(self)->setText(text);
}

void cllaun::widget::LineEdit::selectAll() {
    dynamic_cast<QLineEdit*>(self)->selectAll();
}

void cllaun::widget::LineEdit::clear() {
    dynamic_cast<QLineEdit*>(self)->clear();
}

void cllaun::widget::LineEdit::copy() const {
    dynamic_cast<QLineEdit*>(self)->copy();
}
void cllaun::widget::LineEdit::cut() {
    dynamic_cast<QLineEdit*>(self)->cut();
}

void cllaun::widget::LineEdit::paste() {
    dynamic_cast<QLineEdit*>(self)->paste();
}

void cllaun::widget::LineEdit::redo() {
    dynamic_cast<QLineEdit*>(self)->redo();
}

void cllaun::widget::LineEdit::undo() {
    dynamic_cast<QLineEdit*>(self)->undo();
}
