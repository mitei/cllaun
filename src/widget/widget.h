#pragma once

#include <QObject>
#include <QScriptValue>
class QWidget;

namespace cllaun {
namespace widget {

class Widget : public QObject {
    Q_OBJECT

    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
    Q_PROPERTY(int width READ getWidth WRITE setWidth)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(QScriptValue shortcut READ getShortcut)

public:
    Widget(QWidget* _self, QWidget* parent = nullptr);
    virtual ~Widget();
    QWidget* getQWidget();
    bool eventFilter(QObject* obj, QEvent* event);

    int getX() const;         void setX(int x);
    int getY() const;         void setY(int y);
    int getWidth() const;     void setWidth(int w);
    int getHeight() const;    void setHeight(int h);
    const QScriptValue& getShortcut() const;

public slots:
    void move(int x, int y);
    void resize(int w, int h);
    void show();
    void hide();

protected:
    QWidget* self;

private:
    QScriptValue shortcut;
};

}
}
