#pragma once

#include <QApplication>
#include <QVector>
#include <QDir>
#include <QScriptEngine>

#include "dirs.h"

namespace cllaun {
    class Core {
    public:
        Core(int argc, char **argv);
        ~Core();
        Core* Instance() { return self; }
        static inline const Dirs& PluginDirs() { return self->plugin_dirs; }
        static inline const Dirs& SkinDirs() { return self->skin_dirs; }
        static inline const Dirs& ConfigDirs() { return self->config_dirs; }
        static inline QApplication* App() { return &(self->app); }
        static inline QScriptEngine* Engine() { return &(self->engine); }

    private:
        Dirs plugin_dirs;
        Dirs skin_dirs;
        Dirs config_dirs;
        QApplication app;
        QScriptEngine engine;

    private:
        Core(const Core&);
        Core& operator=(const Core&);
        static Core* self;
    };
}
