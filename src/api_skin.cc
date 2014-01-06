#include "api_skin.h"

#include <QApplication>
#include <QScriptEngine>

#include "api.h"
#include "skin.h"


cllaun::Skin* cllaun::API_Skin::global_skin = nullptr;

cllaun::API_Skin::API_Skin(QScriptEngine *engine, QApplication *app) {
    if (global_skin == nullptr) {
        global_skin = new cllaun::Skin(app);
        global_skin->dirs() << app->applicationDirPath() + "/skins";
    }
    QScriptValue skin_obj = engine->newQObject(global_skin);
    engine->globalObject().setProperty("skin", skin_obj, QScriptValue::Undeletable|QScriptValue::ReadOnly);
}

cllaun::API_Skin::~API_Skin() {
    delete global_skin;
    global_skin = nullptr;
}

cllaun::Skin* cllaun::API_Skin::globalSkin() {
    return global_skin;
}
