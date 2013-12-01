#pragma once

#include <QDir>
#include <QVector>
#include <QApplication>
#include <QScriptEngine>

class QScriptEngine;

namespace cllaun {
    class Core {
    public:
        Core(int argc, char **argv);
        ~Core();
        Core* Instance() { return self; }
        static inline const QVector<QDir>& PluginDirs() { return self->plugin_dirs; }
        static inline const QVector<QDir>& SkinDirs() { return self->skin_dirs; }
        static inline const QVector<QDir>& ConfigDirs() { return self->config_dirs; }
        static inline QApplication* App() { return &(self->app); }
        static inline QScriptEngine* Engine() { return &(self->engine); }

    private:
        QVector<QDir> plugin_dirs;
        QVector<QDir> skin_dirs;
        QVector<QDir> config_dirs;
        QApplication app;
        QScriptEngine engine;

    private:
        Core(const Core&);
        Core& operator=(const Core&);
        static Core* self;
    };
}
