#include "widget/line_edit.h"
#include <QWidget>
#include <QLineEdit>

/*!
 * @brief コンストラクタ
 *
 * @param tarent 親ウィジェット
 */
cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : AbstractWidget(parent), self(new QLineEdit(parent))
{
    initialize(self);
    connect(self, SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
    connect(self, SIGNAL(cursorPositionChanged(int,int)),
            this, SLOT(emitCursorPositionChanged(int,int)));
    connect(self, SIGNAL(editingFinished()),
            this, SLOT(emitEditingFinished()));
    connect(self, SIGNAL(selectionChanged()),
            this, SLOT(emitSelectionChanged()));
    connect(self, SIGNAL(textChanged(QString)),
            this, SLOT(emitTextChanged(QString)));
    connect(self, SIGNAL(textEdited(QString)),
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
    return self->text();
}

int cllaun::widget::LineEdit::getCursorPosition() const {
    return self->cursorPosition();
}

void cllaun::widget::LineEdit::setCursorPosition(int pos) {
    self->setCursorPosition(pos);
}

QString cllaun::widget::LineEdit::getSelectedText() const {
    return self->selectedText();
}

int cllaun::widget::LineEdit::getMaxLength() const {
    return self->maxLength();
}

void cllaun::widget::LineEdit::setMaxLength(int length) {
    self->setMaxLength(length);
}

void cllaun::widget::LineEdit::setSelection(int start, int length) {
    self->setSelection(start, length);
}

void cllaun::widget::LineEdit::home(bool mark) {
    self->home(mark);
}

void cllaun::widget::LineEdit::end(bool mark) {
    self->end(mark);
}

void cllaun::widget::LineEdit::deselect() {
    self->deselect();
}

void cllaun::widget::LineEdit::setText(const QString& text) {
    self->setText(text);
}

void cllaun::widget::LineEdit::selectAll() {
    self->selectAll();
}

void cllaun::widget::LineEdit::clear() {
    self->clear();
}

void cllaun::widget::LineEdit::copy() const {
    self->copy();
}
void cllaun::widget::LineEdit::cut() {
    self->cut();
}

void cllaun::widget::LineEdit::paste() {
    self->paste();
}

void cllaun::widget::LineEdit::redo() {
    self->redo();
}

void cllaun::widget::LineEdit::undo() {
    self->undo();
}
