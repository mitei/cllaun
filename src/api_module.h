#pragma once

class QScriptEngine;

namespace cllaun {

class API_Module {
public:
    API_Module(QScriptEngine* engine);
private:
    API_Module();
};

}
