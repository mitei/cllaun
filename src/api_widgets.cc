#include "api_widgets.h"

#include <QScriptEngine>

#include "api.h"


cllaun::API_Widgets::API_Widgets(QScriptEngine *engine)
    : parent_window(new QMainWindow),
      window(new QWidget),
      command_line(new QLineEdit)
{
    window->setParent(parent_window, Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    window->setAttribute(Qt::WA_TranslucentBackground);
    window->setObjectName("window");
    command_line->setParent(window);
    command_line->setObjectName("commandLine");

    engine->globalObject().setProperty("window", engine->newQObject(window));
    engine->globalObject().setProperty("commandLine", engine->newQObject(command_line));
}

cllaun::API_Widgets::~API_Widgets() {
    delete parent_window;
}
