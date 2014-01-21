#pragma once

class QScriptEngine;

namespace cllaun {

class API_Plugin {
public:
    API_Plugin(QScriptEngine* engine);
private:
    API_Plugin();
};

}
