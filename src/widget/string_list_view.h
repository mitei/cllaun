#pragma once

#include <QListView>
#include <QStringListModel>
#include "abstract_widget.h"

namespace cllaun {
namespace widget {

class StringListView : public AbstractWidget {
    Q_OBJECT
    Q_PROPERTY(QStringList data READ getData WRITE setData)
    Q_PROPERTY(int index READ getCurrentIndex WRITE setCurrentIndex)

public:
    StringListView(QWidget* parent = nullptr);
    QWidget* getQWidget() { return self; }

    /* property */
    QStringList getData() const;
    void setData(const QStringList& data);
    int getCurrentIndex() const;
    void setCurrentIndex(int i);

signals:
    void activated(int index);

private slots:
    void emitActivated(const QModelIndex& index);

protected:
    QListView* self;
    QStringListModel* model;
};

}
}

