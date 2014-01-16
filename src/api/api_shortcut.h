#pragma once

class QScriptEngine;

namespace cllaun {

class ShortcutClass;

class API_Shortcut {
public:
    API_Shortcut(QScriptEngine* engine);
    ~API_Shortcut();
private:
    ShortcutClass* shortcut_cls;
    API_Shortcut();
};

}
