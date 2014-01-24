#include "api_widgets.h"
#include <QScriptEngine>
#include <QMainWindow>
#include "widget/widget.h"
#include "widget/line_edit.h"
#include "widget/string_list_view.h"

/*!
 * @brief Widgets-api の初期化
 */
cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : api_shortcut(engine)
{
    parent_window = new QMainWindow;

    window = new widget::Widget(parent_window);
    window->getQWidget()->setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    window->getQWidget()->setAttribute(Qt::WA_TranslucentBackground);
    command_line = new widget::LineEdit(window->getQWidget());
    list_view = new widget::StringListView(window->getQWidget());

    window->getQWidget()->setObjectName("window");
    command_line->getQWidget()->setObjectName("commandLine");
    list_view->getQWidget()->setObjectName("listView");

    engine->globalObject().setProperty("window", engine->newQObject(window));
    engine->globalObject().setProperty("commandLine", engine->newQObject(command_line));
    engine->globalObject().setProperty("listView", engine->newQObject(list_view));
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
}
