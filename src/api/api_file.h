#pragma once

class QScriptEngine;
class QScriptValue;
class QScriptContext;

namespace cllaun {

class API_File {
public:
    API_File(QScriptEngine* engine);

    static QScriptValue fileConstructor(QScriptContext*, QScriptEngine*, void*);
    static QScriptValue File_rename(QScriptContext*, QScriptEngine*);
    static QScriptValue File_copy(QScriptContext*, QScriptEngine*);
    static QScriptValue File_remove(QScriptContext*, QScriptEngine*);
    static QScriptValue File_exists(QScriptContext*, QScriptEngine*);
    static QScriptValue File_link(QScriptContext*, QScriptEngine*);

private:
    API_File();
};

}
