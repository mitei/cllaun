#pragma once

/*
 * sys =            {};
 * sys.execute =    function(path, args) {};
 * sys.open =       function(path) {};
 * sys.exit =       function(code) {};
 */

#include <QScriptString>
class QApplication;
class QScriptEngine;
class QScriptValue;
class QScriptContext;

namespace cllaun {

class API_Sys {
public:
    API_Sys(QScriptEngine* engine);

    static QScriptValue execute(QScriptContext*, QScriptEngine*);
    static QScriptValue open(QScriptContext*, QScriptEngine*);
    static QScriptValue exit(QScriptContext*, QScriptEngine*);

    static QScriptString str_paths;

private:
    API_Sys();
};

}
