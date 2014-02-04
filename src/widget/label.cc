#include "label.h"
#include <QScriptEngine>


cllaun::widget::Label::Label(QWidget *parent)
    : AbstractWidget(parent), self(new QLabel(parent))
{
    initialize(self);
}

cllaun::widget::Label::~Label() {
}


QString cllaun::widget::Label::getText() const {
    return self->text();
}

void cllaun::widget::Label::setText(const QString& text) {
    self->setText(text);
}

bool cllaun::widget::Label::hasSelectedText() const {
    return self->hasSelectedText();
}

QString cllaun::widget::Label::getSelectedText() const {
    return self->selectedText();
}

int cllaun::widget::Label::getIndent() const {
    return self->indent();
}

void cllaun::widget::Label::setIndent(int indent) {
    self->setIndent(indent);
}

int cllaun::widget::Label::getMargin() const {
    return self->margin();
}

void cllaun::widget::Label::setMargin(int margin) {
    self->setMargin(margin);
}

bool cllaun::widget::Label::getWordWrap() const {
    return self->wordWrap();
}

void cllaun::widget::Label::setWordWrap(bool on) {
    self->setWordWrap(on);
}

bool cllaun::widget::Label::getOpenExternalLinks() const {
    return self->openExternalLinks();
}

void cllaun::widget::Label::setOpenExternalLinks(bool on) {
    self->setOpenExternalLinks(on);
}

Qt::Alignment cllaun::widget::Label::getAlignment() const {
    return self->alignment();
}

void cllaun::widget::Label::setAlignment(Qt::Alignment align) {
    self->setAlignment(align);
}

Qt::TextInteractionFlags cllaun::widget::Label::getInteraction() const {
    return self->textInteractionFlags();
}

void cllaun::widget::Label::setInteraction(Qt::TextInteractionFlags flags) {
    self->setTextInteractionFlags(flags);
}

Qt::TextFormat cllaun::widget::Label::getTextFormat() const {
    return self->textFormat();
}

void cllaun::widget::Label::setTextFormat(Qt::TextFormat format) {
    self->setTextFormat(format);
}


QScriptValue cllaun::widget::Label::alignmentToScriptValue(QScriptEngine* engine, const Qt::Alignment& align) {
    QStringList align_str;
    if (align & Qt::AlignLeft)        align_str << "left";
    if (align & Qt::AlignRight)       align_str << "right";
    if (align & Qt::AlignJustify)     align_str << "justify";
    if (align & Qt::AlignTop)         align_str << "top";
    if (align & Qt::AlignBottom)      align_str << "bottom";
    if (align & Qt::AlignCenter) {
                                      align_str << "center";
    } else {
        if (align & Qt::AlignHCenter) align_str << "hcenter";
        if (align & Qt::AlignVCenter) align_str << "vcenter";
    }
    if (align & Qt::AlignAbsolute)    align_str << "absolute";
    if (align & Qt::AlignLeading)     align_str << "leading";
    if (align & Qt::AlignTrailing)    align_str << "trailing";

    return qScriptValueFromSequence(engine, align_str);
}

void cllaun::widget::Label::alignmentFromScriptValue(const QScriptValue& obj, Qt::Alignment& align) {
    QStringList align_str = qscriptvalue_cast<QStringList>(obj);
    if (align_str.contains("left"))        align |= Qt::AlignLeft;
    if (align_str.contains("right"))       align |= Qt::AlignRight;
    if (align_str.contains("justify"))     align |= Qt::AlignJustify;
    if (align_str.contains("top"))         align |= Qt::AlignTop;
    if (align_str.contains("bottom"))      align |= Qt::AlignBottom;
    if (align_str.contains("center")) {
                                           align |= Qt::AlignCenter;
    } else {
        if (align_str.contains("hcenter")) align |= Qt::AlignHCenter;
        if (align_str.contains("vcenter")) align |= Qt::AlignVCenter;
    }
    if (align_str.contains("absolute"))    align |= Qt::AlignAbsolute;
    if (align_str.contains("leading"))     align |= Qt::AlignLeading;
    if (align_str.contains("trailing"))    align |= Qt::AlignTrailing;
}

QScriptValue cllaun::widget::Label::interactionToScriptValue(QScriptEngine* engine, const Qt::TextInteractionFlags& flags) {
    QStringList flags_str;
    if (flags & Qt::NoTextInteraction)
        return engine->newArray();

    if (flags & Qt::TextSelectableByMouse)     flags_str << "selectableByMouse";
    if (flags & Qt::TextSelectableByKeyboard)  flags_str << "selectableByKeyboard";
    if (flags & Qt::LinksAccessibleByMouse)    flags_str << "linksAccessibleByMouse";
    if (flags & Qt::LinksAccessibleByKeyboard) flags_str << "linksAccessibleByKeyboard";
    if (flags & Qt::TextEditable)              flags_str << "editable";

    return qScriptValueFromSequence(engine, flags_str);
}

void cllaun::widget::Label::interactionFromScriptValue(const QScriptValue& obj, Qt::TextInteractionFlags& flags) {
    QStringList flags_str = qscriptvalue_cast<QStringList>(obj);
    if (flags_str.isEmpty()) {
        flags = Qt::NoTextInteraction;
        return;
    }

    if (flags_str.contains("selectableByMouse"))          flags |= Qt::TextSelectableByMouse;
    if (flags_str.contains("selectableByKeyboard"))       flags |= Qt::TextSelectableByKeyboard;
    if (flags_str.contains("linksAccessibleByMouse"))     flags |= Qt::LinksAccessibleByMouse;
    if (flags_str.contains("linksAccessibleByKeyboard"))  flags |= Qt::LinksAccessibleByKeyboard;
    if (flags_str.contains("editable"))                   flags |= Qt::TextEditable;
}

QScriptValue cllaun::widget::Label::textformatToScriptValue(QScriptEngine* engine, const Qt::TextFormat& format) {
    QString format_str;
    if (format == Qt::PlainText)       { format_str = "plain"; }
    else if (format == Qt::RichText)   { format_str = "rich"; }
    else                               { format_str = "auto"; }

    return QScriptValue(format_str);
}

void cllaun::widget::Label::textformatFromScriptValue(const QScriptValue& obj, Qt::TextFormat& format) {
    QString format_str = obj.toString();
    if (format_str == "plain")       { format = Qt::PlainText; }
    else if (format_str == "rich")   { format = Qt::RichText; }
    else                             { format = Qt::AutoText; }
}