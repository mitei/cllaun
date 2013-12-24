#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLineEdit>

class QScriptEngine;

namespace cllaun {

class API_Widgets {
public:
    API_Widgets(QScriptEngine* engine);
    ~API_Widgets();

private:
    QMainWindow* parent_window;
    QWidget* window;
    QLineEdit* command_line;

private:
    API_Widgets();
};

}
