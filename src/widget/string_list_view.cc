#include "string_list_view.h"


cllaun::widget::StringListView::StringListView(QWidget* parent)
    : self(parent)
{
    self.setModel(&model);
    initialize(&self);
}

QStringList cllaun::widget::StringListView::getData() const {
    return model.stringList();
}

void cllaun::widget::StringListView::setData(const QStringList& data) {
    model.setStringList(data);
}
