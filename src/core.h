#pragma once

#include <QVector>
#include <QScriptEngine>

class QApplication;

namespace cllaun {

class Core {
public:
    Core();
    ~Core();
    Core* Instance() { return self; }
    static inline QScriptEngine* Engine() { return &(self->engine); }

private:
    QScriptEngine engine;

private:
    Core(const Core&);
    Core& operator=(const Core&);
    static Core* self;
};

}
