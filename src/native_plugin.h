#pragma once

#include <QHash>
#include <QString>

#include "dirs.h"

class QLibrary;

namespace cllaun {

class NativePlugin {
public:
    NativePlugin();
    ~NativePlugin();
    QLibrary* Load(const QString& name);
    bool Unload(const QString& name);
    inline void AddSearchPath(const QString& dir_path) { search_paths << dir_path; }

private:
    typedef QHash<QString, QLibrary*> Plugins;

private:
    inline void Unload(Plugins::iterator);

private:
    Dirs search_paths;
    Plugins plugins;
};

}
