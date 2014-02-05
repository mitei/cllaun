#pragma once

#include <QScriptable>
#include <QObject>
class QWidget;

namespace cllaun {
namespace widget {

class WidgetProto : public QObject, public QScriptable {
    Q_OBJECT

public:
    WidgetProto(QObject* parent = nullptr): QObject(parent) { }

public slots:
    void move(int x, int y);
    void resize(int w, int h);
    void show();
    void hide();
    void close();
    void setFocus();

protected:
    inline QWidget* getThis();
};

}
}
