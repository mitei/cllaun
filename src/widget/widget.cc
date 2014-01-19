#include "widget/widget.h"
#include <QWidget>
#include <QEvent>
#include <QKeyEvent>
#include <QKeySequence>
#include <QScriptEngine>
#include "api/api_shortcut.h"

cllaun::widget::Widget::Widget(QWidget* _self, QWidget* parent)
    : self(_self), shortcut(API_Shortcut::newShortcutObject(this))
{
    if (parent != nullptr) {
        self->setParent(parent);
    }
    self->installEventFilter(this);
}

cllaun::widget::Widget::~Widget() {
    delete self;
}

QWidget* cllaun::widget::Widget::getQWidget() {
    return self;
}

int cllaun::widget::Widget::getX() const {
    return self->x();
}

void cllaun::widget::Widget::setX(int x) {
    self->move(x, self->y());
}

int cllaun::widget::Widget::getY() const {
    return self->y();
}

void cllaun::widget::Widget::setY(int y) {
    self->move(self->x(), y);
}

int cllaun::widget::Widget::getWidth() const {
    return self->width();
}

void cllaun::widget::Widget::setWidth(int w) {
    self->resize(w, self->height());
}

int cllaun::widget::Widget::getHeight() const {
    return self->height();
}

void cllaun::widget::Widget::setHeight(int h) {
    self->resize(self->width(), h);
}

const QScriptValue& cllaun::widget::Widget::getShortcut() const {
    return shortcut;
}

void cllaun::widget::Widget::move(int x, int y) {
    self->move(x, y);
}

void cllaun::widget::Widget::resize(int w, int h) {
    self->resize(w, h);
}

void cllaun::widget::Widget::show() {
    self->show();
}

void cllaun::widget::Widget::hide() {
    self->hide();
}

bool cllaun::widget::Widget::eventFilter(QObject* obj, QEvent* e) {
    switch (e->type()) {
    case QEvent::ShortcutOverride:
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
    return false;
}
