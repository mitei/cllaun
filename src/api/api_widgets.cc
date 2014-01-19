#include "api_widgets.h"
#include <QScriptEngine>
#include <QMainWindow>
#include "widget/widget.h"
#include "widget/line_edit.h"

cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : api_shortcut(engine)
{
    parent_window = new QMainWindow;
    window = new widget::Widget(new QWidget);
    command_line = new widget::LineEdit;
    window->getQWidget()->setParent(parent_window, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    window->getQWidget()->setAttribute(Qt::WA_TranslucentBackground);
    window->getQWidget()->setObjectName("window");
    command_line->getQWidget()->setParent(window->getQWidget());
    command_line->getQWidget()->setObjectName("commandLine");

    engine->globalObject().setProperty("window", engine->newQObject(window));
    engine->globalObject().setProperty("commandLine", engine->newQObject(command_line));
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
}
