#pragma once

#include <QScriptable>
#include <QObject>
class QLabel;

namespace cllaun {
namespace widget {

class LabelProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    LabelProto(QObject* parent = nullptr): QObject(parent) { }

public slots:
    // -- Add some prototype methods here.

protected:
    inline QLabel* getThis();
};

}
}
