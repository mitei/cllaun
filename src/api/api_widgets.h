#pragma once

#include <QObject>

class QScriptEngine;
class QMainWindow;

namespace cllaun {

namespace widget {
class Widget;
class LineEdit;
}


class API_Widgets {
public:
    API_Widgets(QScriptEngine* engine);
    ~API_Widgets();

private:
    QMainWindow* parent_window;
    widget::Widget* window;
    widget::LineEdit* command_line;

private:
    API_Widgets();
};

}
