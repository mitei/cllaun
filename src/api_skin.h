#pragma once

class QApplication;
class QScriptEngine;

namespace cllaun {

class Skin;

class API_Skin {
public:
    API_Skin(QScriptEngine* engine, QApplication* app);
    ~API_Skin();
    static Skin* globalSkin();
private:
    static Skin* global_skin;
private:
    API_Skin();
};

}
