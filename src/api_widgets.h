#pragma once

#include <QObject>

class QScriptEngine;
class QMainWindow;
class QWidget;
class QLineEdit;
class QString;

namespace cllaun {

class Widget : public QObject {
    Q_OBJECT

    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
    Q_PROPERTY(int width READ getWidth WRITE setWidth)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)

public:
    Widget(QWidget* _self, QWidget* parent = nullptr);
    virtual ~Widget();
    QWidget* getQWidget();

    int getX();         void setX(int x);
    int getY();         void setY(int y);
    int getWidth();     void setWidth(int w);
    int getHeight();    void setHeight(int h);

public slots:
    void move(int x, int y);
    void resize(int w, int h);
    void show();
    void hide();

protected:
    QWidget* self;
};

class LineEdit : public Widget {
    Q_OBJECT

    Q_PROPERTY(QString text READ getText WRITE setText)

public:
    LineEdit(QWidget* parent = nullptr);
    virtual ~LineEdit();

    QString getText();  void setText(const QString& text);

signals:
    void returnPressed();

private slots:
    void emitReturnPressed();
};

class API_Widgets {
public:
    API_Widgets(QScriptEngine* engine);
    ~API_Widgets();

private:
    QMainWindow* parent_window;
    Widget* window;
    LineEdit* command_line;

private:
    API_Widgets();
};

}
