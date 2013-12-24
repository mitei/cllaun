#pragma once

class QApplication;
class QScriptEngine;

namespace cllaun {

class API_Skin {
public:
    API_Skin(QScriptEngine* engine, QApplication* app);
private:
    API_Skin();
};

}
