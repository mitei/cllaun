#pragma once

/*!
 * @brief 各種ウィジェットのコンストラクタおよびデフォルトウィジェットの提供
 *
 * window = Widget;
 * commandLine = LineEdit;
 */

#include <QObject>
#include "api/api_shortcut.h"

class QScriptEngine;
class QMainWindow;

namespace cllaun {

namespace widget {
class Widget;
class LineEdit;
class StringListView;
}

class API_Widgets {
public:
    API_Widgets(QScriptEngine* engine);
    ~API_Widgets();

private:
    QMainWindow* parent_window;
    widget::Widget* window;
    widget::LineEdit* command_line;
    widget::StringListView* list_view;
    API_Shortcut api_shortcut;

private:
    API_Widgets();
};

}
