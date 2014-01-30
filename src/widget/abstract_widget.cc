#include "widget/abstract_widget.h"
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include <QScriptEngine>
#include "api/api_shortcut.h"

/*!
 * @brief コンストラクタ
 *
 * @param _self   Widget の実体である QWidget
 * @param parent  親ウィジェット
 */
cllaun::widget::AbstractWidget::AbstractWidget(QObject* parent)
    : QObject(parent)
{
}

void cllaun::widget::AbstractWidget::initialize(QWidget* self) {
    shortcut = API_Shortcut::newShortcutObject(self);
    self->installEventFilter(this);
}


/*
 * ACCESSOR
 */
int cllaun::widget::AbstractWidget::getX() {
    return getQWidget()->x();
}

void cllaun::widget::AbstractWidget::setX(int x) {
    getQWidget()->move(x, getQWidget()->y());
}

int cllaun::widget::AbstractWidget::getY() {
    return getQWidget()->y();
}

void cllaun::widget::AbstractWidget::setY(int y) {
    getQWidget()->move(getQWidget()->x(), y);
}

int cllaun::widget::AbstractWidget::getWidth() {
    return getQWidget()->width();
}

void cllaun::widget::AbstractWidget::setWidth(int w) {
    getQWidget()->resize(w, getQWidget()->height());
}

int cllaun::widget::AbstractWidget::getHeight() {
    return getQWidget()->height();
}

void cllaun::widget::AbstractWidget::setHeight(int h) {
    getQWidget()->resize(getQWidget()->width(), h);
}

const QScriptValue& cllaun::widget::AbstractWidget::getShortcut() const {
    return shortcut;
}

/*!
 * @brief ウィジェットの移動
 *
 * @param x  移動先の X 座標
 * @param y  移動先の Y 座標
 */
void cllaun::widget::AbstractWidget::move(int x, int y) {
    getQWidget()->move(x, y);
}

/*!
 * @brief ウィジェットのリサイズ
 *
 * @param w  リサイズ後の幅
 * @param h  リサイズ後の高さ
 */
void cllaun::widget::AbstractWidget::resize(int w, int h) {
    getQWidget()->resize(w, h);
}

/*!
 * @brief ウィジェットを表示する
 */
void cllaun::widget::AbstractWidget::show() {
    getQWidget()->show();
}

/*!
 * @brief ウィジェットを非表示にする
 */
void cllaun::widget::AbstractWidget::hide() {
    getQWidget()->hide();
}

void cllaun::widget::AbstractWidget::setFocus() {
    getQWidget()->setFocus();
}

/*!
 * @brief デフォルトのショートカットを QShortcut で上書きできるようにするイベントフィルタ
 */
bool cllaun::widget::AbstractWidget::eventFilter(QObject* obj, QEvent* e) {
    switch (e->type()) {
    case QEvent::ShortcutOverride: {
        QKeyEvent* ke = static_cast<QKeyEvent*>(e);
        if (ke == QKeySequence::AddTab ||
            ke == QKeySequence::Back ||
            ke == QKeySequence::Bold ||
            ke == QKeySequence::Close ||
            ke == QKeySequence::Copy ||
            ke == QKeySequence::Cut ||
            ke == QKeySequence::Delete ||
            ke == QKeySequence::DeleteEndOfLine ||
            ke == QKeySequence::DeleteEndOfWord ||
            ke == QKeySequence::DeleteStartOfWord ||
            ke == QKeySequence::Find ||
            ke == QKeySequence::FindNext ||
            ke == QKeySequence::FindPrevious ||
            ke == QKeySequence::Forward ||
            ke == QKeySequence::HelpContents ||
            ke == QKeySequence::InsertLineSeparator ||
            ke == QKeySequence::InsertParagraphSeparator ||
            ke == QKeySequence::Italic ||
            ke == QKeySequence::MoveToEndOfBlock ||
            ke == QKeySequence::MoveToEndOfDocument ||
            ke == QKeySequence::MoveToEndOfLine ||
            ke == QKeySequence::MoveToNextChar ||
            ke == QKeySequence::MoveToNextLine ||
            ke == QKeySequence::MoveToNextPage ||
            ke == QKeySequence::MoveToNextWord ||
            ke == QKeySequence::MoveToPreviousChar ||
            ke == QKeySequence::MoveToPreviousLine ||
            ke == QKeySequence::MoveToPreviousPage ||
            ke == QKeySequence::MoveToPreviousWord ||
            ke == QKeySequence::MoveToStartOfBlock ||
            ke == QKeySequence::MoveToStartOfDocument ||
            ke == QKeySequence::MoveToStartOfLine ||
            ke == QKeySequence::New ||
            ke == QKeySequence::NextChild ||
            ke == QKeySequence::Open ||
            ke == QKeySequence::Paste ||
            ke == QKeySequence::Preferences ||
            ke == QKeySequence::PreviousChild ||
            ke == QKeySequence::Print ||
            ke == QKeySequence::Quit ||
            ke == QKeySequence::Redo ||
            ke == QKeySequence::Refresh ||
            ke == QKeySequence::Replace ||
            ke == QKeySequence::SaveAs ||
            ke == QKeySequence::Save ||
            ke == QKeySequence::SelectAll ||
            ke == QKeySequence::SelectEndOfBlock ||
            ke == QKeySequence::SelectEndOfDocument ||
            ke == QKeySequence::SelectEndOfLine ||
            ke == QKeySequence::SelectNextChar ||
            ke == QKeySequence::SelectNextLine ||
            ke == QKeySequence::SelectNextPage ||
            ke == QKeySequence::SelectNextWord ||
            ke == QKeySequence::SelectPreviousChar ||
            ke == QKeySequence::SelectPreviousLine ||
            ke == QKeySequence::SelectPreviousPage ||
            ke == QKeySequence::SelectPreviousWord ||
            ke == QKeySequence::SelectStartOfBlock ||
            ke == QKeySequence::SelectStartOfDocument ||
            ke == QKeySequence::SelectStartOfLine ||
            ke == QKeySequence::Underline ||
            ke == QKeySequence::Undo ||
            ke == QKeySequence::UnknownKey ||
            ke == QKeySequence::WhatsThis ||
            ke == QKeySequence::ZoomIn ||
            ke == QKeySequence::ZoomOut ||
            ke == QKeySequence::FullScreen )
        {
            return true;
        }
    }
    }
    return false;
}
