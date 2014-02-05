#include "push_button.h"
#include <QVariant>

cllaun::widget::PushButton::PushButton(QWidget *parent)
    : QPushButton(parent)
{
    setProperty("x", QVariant());
}
