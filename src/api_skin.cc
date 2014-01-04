#include "api_skin.h"

#include <QApplication>
#include <QScriptEngine>

#include "api.h"
#include "skin.h"


cllaun::API_Skin::API_Skin(QScriptEngine *engine, QApplication *app) {
    cllaun::Skin* skin = new cllaun::Skin(app);
    skin->dirs() << app->applicationDirPath() + "/skins";

    QScriptValue skin_obj = engine->newQObject(skin, QScriptEngine::AutoOwnership);
    engine->globalObject().setProperty("skin", skin_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}
