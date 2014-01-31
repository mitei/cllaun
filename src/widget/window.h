#pragma once

#include "widget.h"

namespace cllaun {
namespace widget {

/*!
 * @class Widget
 * @brief QWidget のラッパ
 *
 * QWidget は Qt Script から扱うには余計なプロパテイが多いため、ラッパで隠す。
 */
class Window : public Widget {
    Q_OBJECT
    Q_PROPERTY(QString windowTitle READ getWindowTitle WRITE setWindowTitle)
    Q_PROPERTY(bool frameLess READ isFrameless WRITE setFrameless)
    //Q_PROPERTY(bool noDropShadow READ isNoDropShadow WRITE setNoDropShadow)
    Q_PROPERTY(bool staysOnTop READ isStaysOnTop WRITE setStaysOnTop)
    Q_PROPERTY(bool staysOnBottom READ isStaysOnBottom WRITE setStaysOnBottom)
    //Q_PROPERTY(bool acceptFocus READ isAcceptFocus WRITE setAcceptFocus)
    //Q_PROPERTY(bool hasTitleBar READ hasTitleBar WRITE setHasTitleBar)
    Q_PROPERTY(bool hasMinimizeButton READ hasMinimizeButton WRITE setHasMinimizeButton)
    Q_PROPERTY(bool hasMaximizeButton READ hasMaximizeButton WRITE setHasMaximizeButton)
    Q_PROPERTY(bool hasCloseButton READ hasCloseButton WRITE setHasCloseButton)
    Q_PROPERTY(bool hasSystemMenu READ hasSystemMenu WRITE setHasSystemMenu)

public:
    Window(QWidget* parent = nullptr);
    QString getWindowTitle();  void setWindowTitle(const QString& title);
    bool isFrameless();        void setFrameless(bool flag);
    //bool isNoDropShadow();     void setNoDropShadow(bool flag);
    bool isStaysOnTop();       void setStaysOnTop(bool flag);
    bool isStaysOnBottom();    void setStaysOnBottom(bool flag);
    //bool isAcceptFocus();      void setAcceptFocus(bool flag);
    //bool hasTitleBar();        void setHasTitleBar(bool flag);
    bool hasMinimizeButton();  void setHasMinimizeButton(bool flag);
    bool hasMaximizeButton();  void setHasMaximizeButton(bool flag);
    bool hasCloseButton();     void setHasCloseButton(bool flag);
    // for Mac
    bool hasSystemMenu();      void setHasSystemMenu(bool flag);
};

}
}
