#pragma once

#include <QWidget>
#include <QScriptable>
#include <QScriptEngine>

namespace cllaun {
namespace widget {

/*!
 * @class Widget
 * @brief QWidget のラッパ
 *
 * QWidget は Qt Script から扱うには余計なプロパテイが多いため、ラッパで隠す。
 */
class Widget : public QObject, public QScriptable {
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)
    Q_PROPERTY(int y READ y WRITE setY)
    Q_PROPERTY(int width READ width WRITE setWidth)
    Q_PROPERTY(int height READ height WRITE setHeight)
    Q_PROPERTY(QString tooltip READ tooltip WRITE setTooltip)
    Q_PROPERTY(QString styleSheet READ styleSheet WRITE setStyleSheet)
    Q_PROPERTY(QString id READ id WRITE setId)
    Q_PROPERTY(bool translucentBackground READ isTranslucentBackground WRITE setTranslucentBackground)

public:
    Widget(QWidget* parent = nullptr);
    virtual ~Widget();
    virtual void initialize(QWidget* self);

    /* property */
    int x();                 void setX(int _x);
    int y();                 void setY(int _y);
    int width();             void setWidth(int w);
    int height();            void setHeight(int h);
    QString tooltip();       void setTooltip(const QString& t);
    QString styleSheet();    void setStyleSheet(const QString& s);
    QString id();            void setId(const QString& i);
    bool isTranslucentBackground();
    void setTranslucentBackground(bool on);

private:
    inline QWidget* getThis();

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event);
};

}
}

