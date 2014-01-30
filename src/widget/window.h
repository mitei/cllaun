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

public:
    Window(QWidget* parent = nullptr);
};

}
}
