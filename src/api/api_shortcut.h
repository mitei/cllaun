#pragma once

#include <QScriptValue>
class QScriptEngine;

namespace cllaun {

namespace widget {
class Widget;
}
class ShortcutClass;

class API_Shortcut {
public:
    API_Shortcut(QScriptEngine* engine);
    ~API_Shortcut();

    static QScriptValue newShortcutObject(widget::Widget* parent);

private:
    static ShortcutClass* shortcut_cls;
    API_Shortcut();
};

}
