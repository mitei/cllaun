#pragma once

#include <QObject>
#include <QScriptable>
class QAbstractButton;

namespace cllaun {
namespace widget {

class AbstractButtonProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    AbstractButtonProto(QObject* parent = nullptr): QObject(parent) { }

public slots:
    //void animateClick(int msec);
    void click();
    void toggle();

private:
    inline QAbstractButton* getThis();
};

}
}
