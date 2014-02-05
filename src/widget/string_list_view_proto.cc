#include "string_list_view_proto.h"
#include <QScriptEngine>
#include <QListView>

QListView* cllaun::widget::StringListViewProto::getThis() {
    return thisObject().data().toVariant().value<QListView*>();
}
