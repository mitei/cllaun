#include "widget/line_edit.h"
#include <QWidget>
#include <QLineEdit>
#include <QEvent>
#include <QKeyEvent>

cllaun::widget::LineEdit::LineEdit(QWidget* parent)
    : cllaun::widget::Widget(new QLineEdit, parent)
{
    connect(dynamic_cast<QLineEdit*>(this->self), SIGNAL(returnPressed()),
            this, SLOT(emitReturnPressed()));
    //this->getQWidget()->installEventFilter(this);
}

cllaun::widget::LineEdit::~LineEdit() {
}

QString cllaun::widget::LineEdit::getText() const {
    return dynamic_cast<QLineEdit*>(self)->text();
}

void cllaun::widget::LineEdit::setText(const QString& text) {
    dynamic_cast<QLineEdit*>(self)->setText(text);
}

/*
bool cllaun::widget::LineEdit::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyevent = static_cast<QKeyEvent*>(event);
        if (keyevent->matches(QKeySequence::AddTab) ||
            keyevent->matches(QKeySequence::Back) ||
            keyevent->matches(QKeySequence::Bold) ||
            keyevent->matches(QKeySequence::Close) ||
            keyevent->matches(QKeySequence::Copy) ||
            keyevent->matches(QKeySequence::Cut) ||
            keyevent->matches(QKeySequence::Delete) ||
            keyevent->matches(QKeySequence::DeleteEndOfLine) ||
            keyevent->matches(QKeySequence::DeleteEndOfWord) ||
            keyevent->matches(QKeySequence::DeleteStartOfWord) ||
            keyevent->matches(QKeySequence::Find) ||
            keyevent->matches(QKeySequence::FindNext) ||
            keyevent->matches(QKeySequence::FindPrevious) ||
            keyevent->matches(QKeySequence::Forward) ||
            keyevent->matches(QKeySequence::HelpContents) ||
            keyevent->matches(QKeySequence::InsertLineSeparator) ||
            keyevent->matches(QKeySequence::InsertParagraphSeparator) ||
            keyevent->matches(QKeySequence::Italic) ||
            keyevent->matches(QKeySequence::MoveToEndOfBlock) ||
            keyevent->matches(QKeySequence::MoveToEndOfDocument) ||
            keyevent->matches(QKeySequence::MoveToEndOfLine) ||
            keyevent->matches(QKeySequence::MoveToNextChar) ||
            keyevent->matches(QKeySequence::MoveToNextLine) ||
            keyevent->matches(QKeySequence::MoveToNextPage) ||
            keyevent->matches(QKeySequence::MoveToNextWord) ||
            keyevent->matches(QKeySequence::MoveToPreviousChar) ||
            keyevent->matches(QKeySequence::MoveToPreviousLine) ||
            keyevent->matches(QKeySequence::MoveToPreviousPage) ||
            keyevent->matches(QKeySequence::MoveToPreviousWord) ||
            keyevent->matches(QKeySequence::MoveToStartOfBlock) ||
            keyevent->matches(QKeySequence::MoveToStartOfDocument) ||
            keyevent->matches(QKeySequence::MoveToStartOfLine) ||
            keyevent->matches(QKeySequence::New) ||
            keyevent->matches(QKeySequence::NextChild) ||
            keyevent->matches(QKeySequence::Open) ||
            keyevent->matches(QKeySequence::Paste) ||
            keyevent->matches(QKeySequence::Preferences) ||
            keyevent->matches(QKeySequence::PreviousChild) ||
            keyevent->matches(QKeySequence::Print) ||
            keyevent->matches(QKeySequence::Quit) ||
            keyevent->matches(QKeySequence::Redo) ||
            keyevent->matches(QKeySequence::Refresh) ||
            keyevent->matches(QKeySequence::Replace) ||
            keyevent->matches(QKeySequence::SaveAs) ||
            keyevent->matches(QKeySequence::Save) ||
            keyevent->matches(QKeySequence::SelectAll) ||
            keyevent->matches(QKeySequence::SelectEndOfBlock) ||
            keyevent->matches(QKeySequence::SelectEndOfDocument) ||
            keyevent->matches(QKeySequence::SelectEndOfLine) ||
            keyevent->matches(QKeySequence::SelectNextChar) ||
            keyevent->matches(QKeySequence::SelectNextLine) ||
            keyevent->matches(QKeySequence::SelectNextPage) ||
            keyevent->matches(QKeySequence::SelectNextWord) ||
            keyevent->matches(QKeySequence::SelectPreviousChar) ||
            keyevent->matches(QKeySequence::SelectPreviousLine) ||
            keyevent->matches(QKeySequence::SelectPreviousPage) ||
            keyevent->matches(QKeySequence::SelectPreviousWord) ||
            keyevent->matches(QKeySequence::SelectStartOfBlock) ||
            keyevent->matches(QKeySequence::SelectStartOfDocument) ||
            keyevent->matches(QKeySequence::SelectStartOfLine) ||
            keyevent->matches(QKeySequence::Underline) ||
            keyevent->matches(QKeySequence::Undo) ||
            keyevent->matches(QKeySequence::UnknownKey) ||
            keyevent->matches(QKeySequence::WhatsThis) ||
            keyevent->matches(QKeySequence::ZoomIn) ||
            keyevent->matches(QKeySequence::ZoomOut) ||
            keyevent->matches(QKeySequence::FullScreen))
        {
            return true;
        }
    }
    return false;
}
*/

void cllaun::widget::LineEdit::emitReturnPressed() {
    emit returnPressed();
}

void cllaun::widget::LineEdit::selectAll() {
    dynamic_cast<QLineEdit*>(self)->selectAll();
}
