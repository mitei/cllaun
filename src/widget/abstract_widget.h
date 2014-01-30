#pragma once

#include <QObject>
#include <QScriptValue>
class QWidget;

namespace cllaun {
namespace widget {

class AbstractWidget : public QObject {
    Q_OBJECT
    Q_PROPERTY(int x READ getX WRITE setX)
    Q_PROPERTY(int y READ getY WRITE setY)
    Q_PROPERTY(int width READ getWidth WRITE setWidth)
    Q_PROPERTY(int height READ getHeight WRITE setHeight)
    Q_PROPERTY(QScriptValue shortcut READ getShortcut)

public:
    AbstractWidget(QObject* parent = nullptr);
    virtual ~AbstractWidget() { }
    virtual QWidget* getQWidget() = 0;

    // デフォルトのショートカットを上書き可能にするイベントフィルタ
    bool eventFilter(QObject* obj, QEvent* event);

    /* property */
    int getX();         void setX(int x);
    int getY();         void setY(int y);
    int getWidth();     void setWidth(int w);
    int getHeight();    void setHeight(int h);
    const QScriptValue& getShortcut() const;

public slots:
    // ウィジェットを移動する
    void move(int x, int y);
    // ウィジェットのサイズを変更する
    void resize(int w, int h);
    // ウィジェットを表示する
    void show();
    // ウィジェットを非表示にする
    void hide();
    void setFocus();

protected:
    void initialize(QWidget* self);

private:
    QScriptValue shortcut; /*!< ショートカット */
};

}
}
