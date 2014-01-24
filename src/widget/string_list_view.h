#pragma once

#include <QListView>
#include <QStringListModel>
#include "abstract_widget.h"

namespace cllaun {
namespace widget {

class StringListView : public AbstractWidget {
    Q_OBJECT
    Q_PROPERTY(QStringList data READ getData WRITE setData)

public:
    StringListView(QWidget* parent = nullptr);
    QWidget* getQWidget() { return &self; }

    /* property */
    QStringList getData() const;
    void setData(const QStringList& data);

private:
    QListView self;
    QStringListModel model;
};

}
}

