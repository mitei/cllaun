#pragma once

#include "widget/abstract_button.h"
#include <QPushButton>

namespace cllaun {
namespace widget {

class PushButton : public AbstractButton {
    Q_OBJECT
    //Q_PROPERTY(bool autoDefault READ autoDefault WRITE setAutoDefault)
    //Q_PROPERTY(bool isDefault READ isDefault WRITE setDefault)
    //Q_PROPERTY(bool flat READ flat WRITE setFlat)

public:
    PushButton(QWidget* parent = nullptr);

    /* property */
    //bool autoDefault();     void setAutoDefault(bool);
    //bool isDefault();       void setDefault(bool);
    //bool flat();            void setFlat(bool);

private:
    QPushButton* getThis();
};

}
}
