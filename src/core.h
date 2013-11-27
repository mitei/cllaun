#pragma once

#include <QString>
#include <QVector>
#include <QScriptEngine>

class QScriptEngine;

namespace cllaun {
    class Core {
    public:
        Core();
        ~Core();
        Core* Instance() { return self; }
        static inline const QVector<QString>& PluginDirs() { return self->plugin_dirs; }
        static inline const QVector<QString>& SkinDirs() { return self->skin_dirs; }
        static inline const QVector<QString>& ConfigDirs() { return self->config_dirs; }
        static inline QScriptEngine* Engine() { return &(self->engine); }

    private:
        QVector<QString> plugin_dirs;
        QVector<QString> skin_dirs;
        QVector<QString> config_dirs;
        QScriptEngine engine;

    private:
        Core(const Core&);
        Core& operator=(const Core&);
        static Core* self;
    };
}
