#include "api_skin.h"

#include <QApplication>

#include "api.h"
#include "skin.h"


void cllaun::initSkin(QApplication* app) {
    cllaun::Skin* skin = new cllaun::Skin(app);
    skin->dirs() << app->applicationDirPath() + "/skins";

    QScriptValue skin_obj = cllaun::Core::engine()->newQObject(skin, QScriptEngine::AutoOwnership);
    cllaun::Core::engine()->globalObject().setProperty("skin", skin_obj);


}
