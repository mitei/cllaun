#pragma once

#include "abstract_widget.h"
#include <QWidget>

namespace cllaun {
namespace widget {

/*!
 * @class Widget
 * @brief QWidget のラッパ
 *
 * QWidget は Qt Script から扱うには余計なプロパテイが多いため、ラッパで隠す。
 */
class Widget : public AbstractWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    QWidget* getQWidget() { return &self; }

private:
    QWidget self; /*!< ウィジェットの実体 */
};

}
}
