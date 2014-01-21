#include "widget/line_edit.h"
#include <QWidget>
#include <QLineEdit>

/*!
 * @brief コンストラクタ
 *
 * @param parent 親ウィジェット
 */
cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : cllaun::widget::Widget(new QLineEdit, parent)
{
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
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
 * @brief QLineEdit::returnPressed シグナルの代替
 *
 * QLineEdit をラップしているため、スクリプトから QLineEdit::returnPressed シグナルが扱えない。
 * LineEdit 内部の QLineEdit の returnPressed シグナルを LineEdit::emitReturnPressed スロットに接続し、
 * LineEdit::returnPressed シグナルを emit している。
 */
void cllaun::widget::LineEdit::emitReturnPressed() {
    emit returnPressed();
}

/*!
 * @brief LineEdit 上のテキストを選択状態にする。
 */
void cllaun::widget::LineEdit::selectAll() {
    dynamic_cast<QLineEdit*>(self)->selectAll();
}
