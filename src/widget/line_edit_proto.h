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

public slots:
    void undo();
    void setSelection(int start, int length);
    void home(bool mark);
    void end(bool mark);
    void deselect();
    void clear();
    void copy();
    void cut();
    void paste();
    void redo();
    void selectAll();

protected:
    inline QLineEdit* getThis();
};

}
}

