#pragma once

#include "widget/widget.h"
#include <QObject>
class QWidget;

namespace cllaun {
namespace widget {

/*!
 * @class LineEdit
 * @brief QLineEdit のラッパ
 */
class LineEdit : public Widget {
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText)

public:
    LineEdit(QWidget* parent = nullptr);
    virtual ~LineEdit();
    /* property */
    QString getText() const;

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
};

}
}
