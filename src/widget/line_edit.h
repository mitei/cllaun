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
    QString getText() const;  void setText(const QString& text);

signals:
    // QLineEdit::returnPressed シグナルのラッパ
    void returnPressed();

public slots:
    // テキストを選択状態にする
    void selectAll();

private slots:
    // QLineEdit::returnPressed シグナルによって呼び出され、LineEdit::returnPressed シグナルを emit する。
    void emitReturnPressed();
};

}
}
