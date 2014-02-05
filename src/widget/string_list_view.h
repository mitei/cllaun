#pragma once

#include <QListView>
#include <QStringListModel>
#include "widget.h"

namespace cllaun {
namespace widget {

class StringListView : public Widget {
    Q_OBJECT
    Q_PROPERTY(QStringList data READ getData WRITE setData)
    Q_PROPERTY(int index READ getCurrentIndex WRITE setCurrentIndex)

public:
    StringListView(QWidget* parent = nullptr);
    virtual void initialize(QWidget *self);

    /* property */
    QStringList getData() const;
    void setData(const QStringList& data);
    int getCurrentIndex();
    void setCurrentIndex(int i);

signals:
    void activated(int index);

private slots:
    void emitActivated(const QModelIndex& index);

protected:
    QStringListModel* model;

private:
    inline QListView* getThis();
};

}
}

