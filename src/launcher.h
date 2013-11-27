#pragma once

class QString;

namespace cllaun {

int Run(const QString& command);
int Execute(const QString& path, const QString& args);

}
