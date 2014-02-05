#pragma once

#include <QScriptable>
#include <QObject>
class QLineEdit;

namespace cllaun {
namespace widget {

class LineEditProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    LineEditProto(QObject* parent = nullptr): QObject(parent) { }

    Q_INVOKABLE void setSelection(int start, int length);
    Q_INVOKABLE void home(bool mark);
    Q_INVOKABLE void end(bool mark);
    Q_INVOKABLE void deselect();

public slots:
    void clear();
    void copy();
    void cut();
    void paste();
    void redo();
    void selectAll();
    void undo();

protected:
    inline QLineEdit* getThis();
};

}
}

