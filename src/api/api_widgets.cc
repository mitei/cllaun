#include "api_widgets.h"
#include <QScriptEngine>
#include <QMainWindow>
#include "widget/widget.h"
#include "widget/window.h"
#include "widget/label.h"
#include "widget/line_edit.h"
#include "widget/string_list_view.h"
#include "api.h"


QMainWindow* cllaun::API_Widgets::parent_window = nullptr;

template <typename WidgetT>
QScriptValue cllaun::API_Widgets::constructor(QScriptContext* context, QScriptEngine* engine) {
    widget::AbstractWidget* parent_widget = qscriptvalue_cast<widget::AbstractWidget*>(context->argument(0));
    QWidget* parent = (parent_widget != nullptr ? parent_widget->getQWidget() : parent_window);
    WidgetT* widget_p = new WidgetT(parent);
    return engine->newQObject(widget_p, QScriptEngine::AutoOwnership);
}

/*!
 * @brief Widgets-api の初期化
 */
cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : api_shortcut(engine)
{
    if (parent_window == nullptr)
        parent_window = new QMainWindow;

    setMethod(engine, "Widget", constructor<widget::Widget>);
    setMethod(engine, "Window", constructor<widget::Window>);
    setMethod(engine, "Label", constructor<widget::Label>);
    setMethod(engine, "LineEdit", constructor<widget::LineEdit>);
    setMethod(engine, "StringListView", constructor<widget::StringListView>);

    qScriptRegisterMetaType(engine,
                            widget::Label::alignmentToScriptValue,
                            widget::Label::alignmentFromScriptValue);
    qScriptRegisterMetaType(engine,
                            widget::Label::interactionToScriptValue,
                            widget::Label::interactionFromScriptValue);
    qScriptRegisterMetaType(engine,
                            widget::Label::textformatToScriptValue,
                            widget::Label::textformatFromScriptValue);
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
    parent_window = nullptr;
}
