#pragma once

#include <vector>
#include <QString>

class ParserUtil
{
public:
    static std::vector<QString> Tokenize(const QString& words);
private:
    ParserUtil();
};
