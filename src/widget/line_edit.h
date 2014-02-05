#pragma once

#include "widget/widget.h"
#include <QLineEdit>

namespace cllaun {
namespace widget {

/*!
 * @class LineEdit
 * @brief QLineEdit のラッパ
 */
class LineEdit : public Widget {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(int cursorPosition READ getCursorPosition WRITE setCursorPosition)
    Q_PROPERTY(QString slectedText READ getSelectedText)
    Q_PROPERTY(int maxLength READ getMaxLength WRITE setMaxLength)

public:
    LineEdit(QWidget* parent = nullptr);
    virtual ~LineEdit() { }
    virtual void initialize(QWidget* self);

    /* property */
    QString getText();
    int getCursorPosition();    void setCursorPosition(int pos);
    QString getSelectedText();
    int getMaxLength();         void setMaxLength(int length);

public slots:
    void setText(const QString& text);

signals:
    /* QLineEdit シグナルのラッパ */
    void returnPressed();
    void cursorPositionChanged(int old, int _new);
    void editingFinished();
    void selectionChanged();
    void textChanged(const QString& text);
    void textEdited(const QString& text);

private slots:
    /* QLineEdit シグナルによって呼ばれ、対応する LineEdit シグナルを emit する。 */
    void emitReturnPressed() { emit returnPressed(); }
    void emitCursorPositionChanged(int old, int _new) { emit cursorPositionChanged(old, _new); }
    void emitEditingFinished() { emit editingFinished(); }
    void emitSelectionChanged() { emit selectionChanged(); }
    void emitTextChanged(const QString& text) { emit textChanged(text); }
    void emitTextEdited(const QString& text) { emit textEdited(text); }

private:
    inline QLineEdit* getThis();
};

}
}

