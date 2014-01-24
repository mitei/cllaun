#include "widget/widget.h"

cllaun::widget::Widget::Widget(QWidget* parent)
    : self(parent)
{
    initialize(&self);
}
