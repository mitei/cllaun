#pragma once

#include "command.h"

class QString;
class QStringList;

namespace cllaun {

/*!
 * @brief パーサ。
 */
class Parser
{
public:
    // コマンド文字列を受け取り、パースして Command オブジェクトとして返す。
    static Command parse(const QString& src);
    // コマンド文字列を受け取り、トークン単位で区切った文字列リストを返す。
    static QStringList split(QString src);
    // トークンの Command::Type を返す。
    static Command::Type type(const QString& src);

private:
    Parser();
    // utilities for parsing
};

}
