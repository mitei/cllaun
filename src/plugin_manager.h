#pragma once

#include <QHash>
#include <QString>
#include <QLibrary>

class QScriptEngine;

namespace cllaun {

class PluginManager {
public:
    PluginManager(QScriptEngine* engine_ = nullptr);
    ~PluginManager();
    void SetEngine(QScriptEngine* engine_);
    QLibrary* Load(const QString& path);
    bool Unload(const QString& path);
private:
    typedef QHash<QString, QLibrary*> Plugins;
private:
    inline void Unload(Plugins::iterator);
private:
    Plugins plugins;
    QScriptEngine* engine;
};
}
