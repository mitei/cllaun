#include "widget/widget.h"

cllaun::widget::Widget::Widget(QWidget* parent)
    : AbstractWidget(parent), self(new QWidget(parent))
{
    initialize(self);
}
