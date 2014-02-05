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
class QScriptValue;
class QScriptContext;
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

    template <typename WrapT, typename BaseT>
    static QScriptValue constructor(QScriptContext* context, QScriptEngine* engine, void* proto);

private:
    static QMainWindow* parent_window;
    API_Shortcut api_shortcut;

private:
    API_Widgets();
};

}
