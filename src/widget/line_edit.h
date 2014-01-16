#pragma once

#include "widget/widget.h"
#include <QObject>
class QWidget;

namespace cllaun {
namespace widget {

class LineEdit : public Widget {
    Q_OBJECT

    Q_PROPERTY(QString text READ getText WRITE setText)

public:
    LineEdit(QWidget* parent = nullptr);
    virtual ~LineEdit();

    QString getText() const;  void setText(const QString& text);

protected:
    //bool eventFilter(QObject* obj, QEvent* event);

signals:
    void returnPressed();

public slots:
    void selectAll();

private slots:
    void emitReturnPressed();
};

}
}
