#include "api_widgets.h"
#include <QScriptEngine>
#include <QMainWindow>
#include "widget/widget.h"
#include "widget/widget_proto.h"
#include "widget/window.h"
#include "widget/label.h"
#include "widget/label_proto.h"
#include "widget/line_edit.h"
#include "widget/line_edit_proto.h"
#include "widget/string_list_view.h"
#include "widget/string_list_view_proto.h"
#include "api.h"


QMainWindow* cllaun::API_Widgets::parent_window = nullptr;

template <typename WrapT, typename BaseT>
QScriptValue cllaun::API_Widgets::constructor(QScriptContext* context, QScriptEngine* engine, void* proto) {
    // set parent
    QWidget* parent = nullptr;
    if (context->argumentCount() > 0) {
        cllaun::widget::Widget* parent_wrap = qscriptvalue_cast<cllaun::widget::Widget*>(context->argument(0));
        if (parent_wrap != nullptr)
            parent = context->argument(0).data().toVariant().value<QWidget*>();
    }
    BaseT* self = new BaseT(parent);
    self->setAttribute(Qt::WA_DeleteOnClose);
    WrapT* wrap = new WrapT(self);
    wrap->initialize(self);
    //self->installEventFilter(wrap);
    QScriptValue instance = engine->newQObject(wrap);
    instance.setData(engine->newVariant(qVariantFromValue<BaseT*>(self)));
    instance.setPrototype(*static_cast<QScriptValue*>(proto));
    instance.setProperty("shortcut", API_Shortcut::newShortcutObject(self), QScriptValue::Undeletable|QScriptValue::ReadOnly);
    return instance;
}

/*!
 * @brief Widgets-api の初期化
 */
cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : api_shortcut(engine)
{
    if (parent_window == nullptr)
        parent_window = new QMainWindow;

    static QScriptValue widget_proto = engine->newQObject(new widget::WidgetProto(engine));
    setMethod(engine, "Widget", constructor<widget::Widget, QWidget>, &widget_proto);
    setMethod(engine, "Window", constructor<widget::Window, widget::QWindow>, &widget_proto);
    static QScriptValue label_proto = engine->newQObject(new widget::LabelProto(engine));
    label_proto.setPrototype(widget_proto);
    setMethod(engine, "Label", constructor<widget::Label, QLabel>, &label_proto);
    static QScriptValue line_edit_proto = engine->newQObject(new widget::LineEditProto(engine));
    line_edit_proto.setPrototype(widget_proto);
    setMethod(engine, "LineEdit", constructor<widget::LineEdit, QLineEdit>, &line_edit_proto);
    static QScriptValue string_list_view_proto = engine->newQObject(new widget::StringListViewProto(engine));
    string_list_view_proto.setPrototype(widget_proto);
    setMethod(engine, "StringListView", constructor<widget::StringListView, QListView>, &string_list_view_proto);

    /*
    qScriptRegisterMetaType(engine,
                            widget::Label::alignmentToScriptValue,
                            widget::Label::alignmentFromScriptValue);
    qScriptRegisterMetaType(engine,
                            widget::Label::interactionToScriptValue,
                            widget::Label::interactionFromScriptValue);
    qScriptRegisterMetaType(engine,
                            widget::Label::textformatToScriptValue,
                            widget::Label::textformatFromScriptValue);
                            */
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
    parent_window = nullptr;
}
