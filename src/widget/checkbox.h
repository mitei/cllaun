#pragma once

#include "abstract_button.h"
#include <QCheckBox>

namespace cllaun {
namespace widget {

class CheckBox : public AbstractButton {
    Q_OBJECT
    Q_PROPERTY(bool tristate READ isTristate WRITE setTristate)

public:
    CheckBox(QWidget* parent = nullptr);

    /* property */
    bool isTristate();
    void setTristate(bool y = true);

private:
    inline QCheckBox* getThis();
};

}
}

