#pragma once

class QString;

namespace cllaun {
    int Run(const QString& command);
    extern int Execute(const QString& path, const QString& args);
}
