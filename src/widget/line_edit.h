#pragma once

#include "widget/abstract_widget.h"
#include <QObject>
#include <QLineEdit>
class QWidget;

namespace cllaun {
namespace widget {

/*!
 * @class LineEdit
 * @brief QLineEdit のラッパ
 */
class LineEdit : public AbstractWidget {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)
    Q_PROPERTY(int cursorPosition READ getCursorPosition WRITE setCursorPosition)
    Q_PROPERTY(QString slectedText READ getSelectedText)
    Q_PROPERTY(int maxLength READ getMaxLength WRITE setMaxLength)

public:
    LineEdit(QWidget* parent = nullptr);
    virtual ~LineEdit();
    QWidget* getQWidget() { return self; }

    /* property */
    QString getText() const;
    int getCursorPosition() const;    void setCursorPosition(int pos);
    QString getSelectedText() const;
    int getMaxLength() const;         void setMaxLength(int length);

    /* QLineEdit Public Functions ラッパ */
    Q_INVOKABLE void setSelection(int start, int length);
    Q_INVOKABLE void home(bool mark);
    Q_INVOKABLE void end(bool mark);
    Q_INVOKABLE void deselect();

signals:
    /* QLineEdit シグナルのラッパ */
    void returnPressed();
    void cursorPositionChanged(int old, int _new);
    void editingFinished();
    void selectionChanged();
    void textChanged(const QString& text);
    void textEdited(const QString& text);

public slots:
    /* QLineEdit スロットのラッパ */
    void clear();
    void copy() const;
    void cut();
    void paste();
    void redo();
    void selectAll();
    void setText(const QString& text);
    void undo();

private slots:
    /* QLineEdit シグナルによって呼ばれ、対応する LineEdit シグナルを emit する。 */
    void emitReturnPressed() { emit returnPressed(); }
    void emitCursorPositionChanged(int old, int _new) { emit cursorPositionChanged(old, _new); }
    void emitEditingFinished() { emit editingFinished(); }
    void emitSelectionChanged() { emit selectionChanged(); }
    void emitTextChanged(const QString& text) { emit textChanged(text); }
    void emitTextEdited(const QString& text) { emit textEdited(text); }

protected:
    QLineEdit* self;
};

}
}
