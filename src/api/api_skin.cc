#include "api_skin.h"
#include <QApplication>
#include <QScriptEngine>
#include "skin.h"


cllaun::Skin* cllaun::API_Skin::global_skin = nullptr;

/*!
 * @brief Skin-api の初期化
 */
cllaun::API_Skin::API_Skin(QScriptEngine *engine, QApplication *app) {
    QScriptValue skin_obj = Skin::newQObject(engine, app);
    global_skin = qobject_cast<Skin*>(skin_obj.toQObject());
    QStringList default_dirs;
    default_dirs << (app->applicationDirPath() + "/skins");
    skin_obj.setProperty("dirs", qScriptValueFromSequence(engine, default_dirs));

    engine->globalObject().setProperty(
                "skin", skin_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}


/*!
 * @brief Skin インスタンスへのグローバルアクセス
 *
 * @return Skin インスタンス
 */
cllaun::Skin* cllaun::API_Skin::globalSkin() {
    return global_skin;
}
