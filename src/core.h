#pragma once

#include <QVector>
#include <QScriptEngine>

class QApplication;

namespace cllaun {

class Core {
public:
    Core();
    ~Core();
    Core* insntance() { return self; }
    static inline QScriptEngine* engine() { return &(self->_engine); }

private:
    QScriptEngine _engine;

private:
    Core(const Core&);
    Core& operator=(const Core&);
    static Core* self;
};

}
