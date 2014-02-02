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

QString cllaun::widget::AbstractWidget::getTooltip(){
    return getQWidget()->toolTip();
}

void cllaun::widget::AbstractWidget::setTooltip(const QString& text) {
    getQWidget()->setToolTip(text);
}

QString cllaun::widget::AbstractWidget::getStylesheet() {
    return getQWidget()->styleSheet();
}

void cllaun::widget::AbstractWidget::setStylesheet(const QString& stylesheet) {
    getQWidget()->setStyleSheet(stylesheet);
}

bool cllaun::widget::AbstractWidget::isTranslucentBackground() {
    return getQWidget()->testAttribute(Qt::WA_TranslucentBackground);
}

void cllaun::widget::AbstractWidget::setTranslucentBackground(bool flag) {
    getQWidget()->setAttribute(Qt::WA_TranslucentBackground, flag);
}

QString cllaun::widget::AbstractWidget::getId() {
    return getQWidget()->objectName();
}

void cllaun::widget::AbstractWidget::setId(const QString& id) {
    getQWidget()->setObjectName(id);
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
    case QEvent::ShortcutOverride:
        return true;
    default:
        return false;
    }
}
