#pragma once

#include "widget.h"
#include <QLabel>

Q_DECLARE_METATYPE(Qt::Alignment)
Q_DECLARE_METATYPE(Qt::TextInteractionFlags)
Q_DECLARE_METATYPE(Qt::TextFormat)

namespace cllaun {
namespace widget {

class Label : public Widget {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(bool hasSelectedText READ hasSelectedText)
    Q_PROPERTY(QString selectedText READ getSelectedText)
    Q_PROPERTY(int indent READ getIndent WRITE setIndent)
    Q_PROPERTY(int margin READ getMargin WRITE setMargin)
    Q_PROPERTY(bool wordWrap READ getWordWrap WRITE setWordWrap)
    Q_PROPERTY(bool openExternalLinks READ getOpenExternalLinks WRITE setOpenExternalLinks)
    Q_PROPERTY(Qt::Alignment alignment READ getAlignment WRITE setAlignment)
    Q_PROPERTY(Qt::TextInteractionFlags interaction READ getInteraction WRITE setInteraction)
    Q_PROPERTY(Qt::TextFormat textFormat READ getTextFormat WRITE setTextFormat)

public:
    Label(QWidget* parent = nullptr);
    virtual ~Label() { }

    /* property */
    QString getText();
    bool hasSelectedText();
    QString getSelectedText();
    int getIndent();                 void setIndent(int indent);
    int getMargin();                 void setMargin(int margin);
    bool getWordWrap();              void setWordWrap(bool on);
    bool getOpenExternalLinks();     void setOpenExternalLinks(bool on);
    Qt::Alignment getAlignment();    void setAlignment(Qt::Alignment align);
    Qt::TextInteractionFlags getInteraction();
    void setInteraction(Qt::TextInteractionFlags flags);
    Qt::TextFormat getTextFormat();  void setTextFormat(Qt::TextFormat format);

    static QScriptValue alignmentToScriptValue(QScriptEngine* engine, const Qt::Alignment& align);
    static void alignmentFromScriptValue(const QScriptValue& obj, Qt::Alignment& align);
    static QScriptValue interactionToScriptValue(QScriptEngine* engine, const Qt::TextInteractionFlags& flags);
    static void interactionFromScriptValue(const QScriptValue& obj, Qt::TextInteractionFlags& flags);
    static QScriptValue textformatToScriptValue(QScriptEngine* engien, const Qt::TextFormat& format);
    static void textformatFromScriptValue(const QScriptValue& obj, Qt::TextFormat& format);

public slots:
    void setText(const QString& text);

private:
    inline QLabel* getThis();
};

}
}

