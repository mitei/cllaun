#pragma once

#include "widget/abstract_button.h"
#include <QRadioButton>

namespace cllaun {
namespace widget {

class RadioButton : public AbstractButton {
    Q_OBJECT

public:
    RadioButton(QWidget* parent = nullptr);

private:
    inline QRadioButton* getThis();
};

}
}
