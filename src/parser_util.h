#pragma once

#include <vector>
#include <iostream>
#include <QString>
#include <QStringList>

class ParserUtil
{
public:
    static std::vector<QString> Tokenize(const QString& src);
private:
    ParserUtil();
};
