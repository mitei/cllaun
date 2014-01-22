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

/*!
 * @brief LineEdit 上のテキストを取得する
 *
 * @return LineEdit 上のテキスト
 */
QString cllaun::widget::LineEdit::getText() const {
    return dynamic_cast<QLineEdit*>(self)->text();
}

/*!
 * @brief LineEdit のテキストを設定する
 *
 * @param text LineEdit に設定するテキスト
 */
void cllaun::widget::LineEdit::setText(const QString& text) {
    dynamic_cast<QLineEdit*>(self)->setText(text);
}

/*!
 * @brief LineEdit 上のテキストを選択状態にする。
 */
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
