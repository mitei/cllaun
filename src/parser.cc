#include "parser.h"

#include <QString>
#include <QStringList>
#include <QRegExp>

#include "command.h"

/*! パース実行(唯一の公開メソッド) */
cllaun::Command cllaun::Parser::parse(const QString& src) {
    QStringList tokens = split(src);
    QString name = (tokens.size() > 0) ? tokens.at(0)
                                       : QString("");
    Command::Type type = Command::INVALID;

    // case INVALID:
    if (tokens.empty()) {
        return Command();
    }
    // case PLUGIN:
    if (name.startsWith(":")) {
        type = Command::PLUGIN;
        name = name.mid(1);
    // case PATH:
    } else if (name.startsWith("\"") && name.endsWith("\"")) {
        type = Command::PATH;
        name = name.mid(1,name.length() - 2);
    } else if (name.indexOf(":") != -1) {
        type = Command::PATH;
    // case ALIAS:
    } else if (name.startsWith("?")) {
        type = Command::ALIAS;
        name = name.mid(1);
    // default:
    } else {
        type = Command::ANY;
    }

    tokens.pop_front();
    return Command(type, name, tokens);
}

QStringList cllaun::Parser::split(QString src) {
    QStringList tokens;
    QRegExp regex("(\"(\\\\\"|[^\"])*\")|([^ \"]+)");

    int pos = 0;
    while ((pos = regex.indexIn(src, pos)) != -1) {
        tokens << regex.cap(0);
        pos += regex.matchedLength();
    }

    return tokens;
}
