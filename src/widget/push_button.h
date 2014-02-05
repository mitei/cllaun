#pragma once

#include <QPushButton>

namespace cllaun {
namespace widget {

class PushButton : public QPushButton {
    Q_OBJECT
    Q_PROPERTY(int x READ x WRITE setX)

public:
    PushButton(QWidget* parent = nullptr);
    void setX(int _x) { move(_x, y()); }
private slots:
    void click() { }
};

}
}
