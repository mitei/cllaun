#include "string_list_view.h"


cllaun::widget::StringListView::StringListView(QWidget* parent)
    : Widget(parent), model(new QStringListModel(parent))
{
}
cllaun::widget::StringListView::~StringListView() {
    if (model->QObject::parent() == nullptr) { delete model; }
}

QListView* cllaun::widget::StringListView::getThis() {
    return thisObject().data().toVariant().value<QListView*>();
}

void cllaun::widget::StringListView::initialize(QWidget* self) {
    QListView* self_lv = dynamic_cast<QListView*>(self);
    self_lv->setModel(model);
    connect(self_lv, SIGNAL(activated(QModelIndex)),
            this,  SLOT(emitActivated(QModelIndex)));
}

QStringList cllaun::widget::StringListView::getData() const {
    return model->stringList();
}

void cllaun::widget::StringListView::setData(const QStringList& data) {
    model->setStringList(data);
}

int cllaun::widget::StringListView::getCurrentIndex() {
    return getThis()->currentIndex().row();
}

void cllaun::widget::StringListView::setCurrentIndex(int i) {
    getThis()->setCurrentIndex(model->index(i));
}

void cllaun::widget::StringListView::emitActivated(const QModelIndex& index) {
    emit activated(index.row());
}
