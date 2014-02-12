#pragma once

#include <QDir>

class QScriptEngine;
class QScriptValue;
class QScriptContext;

namespace cllaun {

class API_File {
public:
    API_File(QScriptEngine* engine);

private:
    static QScriptValue fileConstructor(QScriptContext*, QScriptEngine*, void*);
    static QScriptValue File_rename(QScriptContext*, QScriptEngine*);
    static QScriptValue File_copy(QScriptContext*, QScriptEngine*);
    static QScriptValue File_remove(QScriptContext*, QScriptEngine*);
    static QScriptValue File_exists(QScriptContext*, QScriptEngine*);
    static QScriptValue File_link(QScriptContext*, QScriptEngine*);

    static QScriptValue dirConstructor(QScriptContext*, QScriptEngine*, void*);
    static QScriptValue Dir_current(QScriptContext*, QScriptEngine*);
    static QScriptValue Dir_home(QScriptContext*, QScriptEngine*);
    static QScriptValue Dir_temp(QScriptContext*, QScriptEngine*);
    static QScriptValue Dir_setCurrent(QScriptContext*, QScriptEngine*);
    static QScriptValue Dir_toNativeSeparators(QScriptContext*, QScriptEngine*);

    static QScriptValue filtersToScriptValue(QScriptEngine*, const QDir::Filters&);
    static void filtersFromScriptValue(const QScriptValue& obj, QDir::Filters& f);
    static QScriptValue sortToScriptValue(QScriptEngine*, const QDir::SortFlags&);
    static void sortFromScriptValue(const QScriptValue& obj, QDir::SortFlags& s);

private:
    API_File();
};

}
