#pragma once

#include <QObject>
#include <QScriptValue>
class QWidget;

namespace cllaun {
namespace widget {

/*!
 * @class Widget
 * @brief QWidget のラッパ
 *
 * QWidget は Qt Script から扱うには余計なプロパテイが多いため、ラッパで隠す。
 */
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
    // 実体の QWidget を取得する。
    QWidget* getQWidget();
    // デフォルトのショートカットを上書き可能にするイベントフィルタ
    bool eventFilter(QObject* obj, QEvent* event);
    /* property */
    int getX() const;         void setX(int x);
    int getY() const;         void setY(int y);
    int getWidth() const;     void setWidth(int w);
    int getHeight() const;    void setHeight(int h);
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

protected:
    QWidget* self; /*!< ウィジェットの実体 */

private:
    QScriptValue shortcut; /*!< ショートカット */
};

}
}
