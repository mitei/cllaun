#include "api_widgets.h"
#include <QScriptEngine>
#include <QMainWindow>
#include "widget/widget.h"
#include "widget/window.h"
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

    /*
    window = new widget::Widget(parent_window);
    window->getQWidget()->setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    window->getQWidget()->setAttribute(Qt::WA_TranslucentBackground);
    command_line = new widget::LineEdit(window->getQWidget());
    list_view = new widget::StringListView(window->getQWidget());

    window->getQWidget()->setObjectName("window");
    command_line->getQWidget()->setObjectName("commandLine");
    list_view->getQWidget()->setObjectName("listView");

    engine->globalObject().setProperty("window", engine->newQObject(window));
    engine->globalObject().setProperty("commandLine", engine->newQObject(command_line));
    engine->globalObject().setProperty("listView", engine->newQObject(list_view));
    */

    setMethod(engine, "Widget", constructor<widget::Widget>);
    setMethod(engine, "Window", constructor<widget::Window>);
    setMethod(engine, "LineEdit", constructor<widget::LineEdit>);
    setMethod(engine, "StringListView", constructor<widget::StringListView>);

}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
    parent_window = nullptr;
}
