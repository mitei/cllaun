#pragma once

/*!
 * @brief スキンの読み込みなどを提供
 *
 * skin = {
 *     read : function(name:String) { ...
 * };
 */

class QApplication;
class QScriptEngine;

namespace cllaun {

class Skin;

class API_Skin {
public:
    API_Skin(QScriptEngine* engine, QApplication* app);
    static Skin* globalSkin();
private:
    static Skin* global_skin;
private:
    API_Skin();
};

}
