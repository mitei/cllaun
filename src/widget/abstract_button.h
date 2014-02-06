#pragma once

#include "widget/widget.h"
class QAbstractButton;

namespace cllaun {
namespace widget {

class AbstractButton : public Widget {
    Q_OBJECT
    Q_PROPERTY(QString text READ text WRITE setText)
    //Q_PROPERTY(bool autoExclusive READ autoExclusive WRITE setAutoExclusive)
    //Q_PROPERTY(bool autoRepeat READ autoRepeat WRITE setAutoRepeat)
    Q_PROPERTY(bool checkable READ checkable WRITE setCheckable)
    Q_PROPERTY(bool checked READ checked WRITE setChecked NOTIFY toggled)
    //Q_PROPERTY(int autoRepeatDelay READ autoRepeatDelay WRITE setAutoRepeatDelay)
    //Q_PROPERTY(int autoRepeatInterval READ autoRepeatInterval WRITE setAutoRepeatInterval)
    //Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    //Q_PROPERTY(QSize iconSize READ iconSize WRITE setIconSize)
    Q_PROPERTY(bool down READ down WRITE setDown)

public:
    AbstractButton(QWidget* parent = nullptr);
    virtual void initialize(QWidget *self);

    /* property */
    QString text();             void setText(const QString&);
    //bool autoExclusive();       void setAutoExclusive(bool);
    //bool autoRepeat();          void setAutoRepeat(bool);
    bool checkable();           void setCheckable(bool);
    bool checked();
    //int autoRepeatDelay();      void setAutoRepeatDelay(int);
    //int autoRepeatInterval();   void setAutoRepeatInterval(int);
    //QIcon icon();               void setIcon(const QIcon&);
    //QSize iconSize();
    bool down();                void setDown(bool);

public slots:
    void setChecked(bool);
    //void setIconSize(const QSize&);

signals:
    void toggled(bool checked);
    void clicked(bool checked = false);
    void pressed();
    void released();

private slots:
    void emitToggled(bool c) { emit toggled(c); }
    void emitClicked(bool c = false) { emit clicked(c); }
    void emitPressed() { emit pressed(); }
    void emitReleased() { emit released(); }

private:
    inline QAbstractButton* getThis();
};

}
}
