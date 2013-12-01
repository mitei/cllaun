#pragma once

#include <QHash>
#include <QString>

class QLibrary;

namespace cllaun {

class PluginManager {
public:
    PluginManager();
    ~PluginManager();
    QLibrary* Load(const QString& path);
    bool Unload(const QString& path);

private:
    typedef QHash<QString, QLibrary*> Plugins;

private:
    inline void Unload(Plugins::iterator);

private:
    Plugins plugins;
};

}
