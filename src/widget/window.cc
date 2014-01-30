#include "window.h"

cllaun::widget::Window::Window(QWidget* parent)
    : Widget(parent)
{
    self->setWindowFlags(Qt::Window);
}
