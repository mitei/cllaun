#pragma once

#include <QScriptable>
#include <QObject>
class QListView;

namespace cllaun {
namespace widget {

class StringListViewProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    StringListViewProto(QObject* parent = nullptr): QObject(parent) { }

public slots:
    // -- Add some prototype methods here.

protected:
    inline QListView* getThis();
};

}
}
