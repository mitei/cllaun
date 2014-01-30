#include "string_list_view.h"


cllaun::widget::StringListView::StringListView(QWidget* parent)
    : AbstractWidget(parent), self(new QListView(parent)), model(new QStringListModel(self))
{
    self->setModel(model);
    initialize(self);

    connect(self, SIGNAL(activated(QModelIndex)),
            this,  SLOT(emitActivated(QModelIndex)));
}

QStringList cllaun::widget::StringListView::getData() const {
    return model->stringList();
}

void cllaun::widget::StringListView::setData(const QStringList& data) {
    model->setStringList(data);
}

int cllaun::widget::StringListView::getCurrentIndex() const {
    return self->currentIndex().row();
}

void cllaun::widget::StringListView::setCurrentIndex(int i) {
    self->setCurrentIndex(model->index(i));
}

void cllaun::widget::StringListView::emitActivated(const QModelIndex& index) {
    emit activated(index.row());
}
