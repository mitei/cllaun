#pragma once

#include <vector>
#include <QString>

class ParserUtil
{
public:
    static std::vector<QString> Split(const QString& words);
private:
    ParserUtil();
};
