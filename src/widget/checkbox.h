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
    void initialize(QWidget* self);

    /* property */
    bool isTristate();
    void setTristate(bool y = true);

signals:
    void stateChanged(int state);

private slots:
    void emitStateChanged(int state) { emit stateChanged(state); }

private:
    inline QCheckBox* getThis();
};

}
}

