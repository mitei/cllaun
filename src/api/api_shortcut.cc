#include "api_shortcut.h"
#include <QScriptEngine>
#include "shortcut_class.h"
#include "widget/widget.h"
#include "global_shortcut_class.h"

cllaun::ShortcutClass* cllaun::API_Shortcut::shortcut_cls = nullptr;

/*!
 * @brief Shortcut-api の初期化
 */
cllaun::API_Shortcut::API_Shortcut(QScriptEngine* engine)
{
    global_shortcut_cls = new GlobalShortcutClass(engine);
    if (shortcut_cls == nullptr) {
        shortcut_cls = new ShortcutClass(engine);
    }
    QScriptValue global_shortcuts =
            engine->newQObject(new GlobalShortcuts(engine), QScriptEngine::QtOwnership);
    QScriptValue global_shortcut_obj = engine->newObject(global_shortcut_cls, global_shortcuts);
    engine->globalObject().setProperty("shortcut", global_shortcut_obj);
}

/*!
 * @brief デストラクタ
 */
cllaun::API_Shortcut::~API_Shortcut() {
    delete shortcut_cls;
    delete global_shortcut_cls;
}


/*!
 * @brief ショートカットオブジェクトの生成
 *
 * Widget の shortcut プロパティを設定するために必要。
 *
 * @param parent  親ウィジェット
 * @return        Shortcuts オブジェクト
 */
QScriptValue cllaun::API_Shortcut::newShortcutObject(widget::Widget* parent) {
    QScriptEngine* engine = shortcut_cls->engine();
    Shortcuts* shortcuts = new Shortcuts(parent->getQWidget());
    QScriptValue shortcuts_obj = engine->newQObject(shortcuts, QScriptEngine::AutoOwnership);
    QScriptValue instance = engine->newObject(shortcut_cls, shortcuts_obj);

    return instance;
}
