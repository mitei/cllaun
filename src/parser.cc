#include "parser.h"

#include <QString>
#include <QStringList>
#include <QRegExp>


/* コマンド文字列をトークン単位で取り出す正規表現文字列
 *   \" :     ダブルクォートで始まり、
 *   \\\\\" : C++ 文字列のエスケープと正規表現のエスケープでややこしいが、
 *            入力値としての \"
 *   | :      または
 *   [^\"] :  ダブルクォート以外の文字
 *   * :      の 0回以上の連続
 *   | :      または
 *   [^ \"] : 半角スペースとダブルクォート以外の文字
 *   + :      の 1回以上の連続
 */
#define COMMAND_TOKEN_REGEXP "(\"(\\\\\"|[^\"])*\")|([^ \"]+)"


/*!
 * @brief コマンド文字列を受け取り、パース結果を Command オブジェクトとして返す。
 *
 * @param src コマンド文字列
 *
 * @return パース結果の Command オブジェクト
 */
cllaun::Command cllaun::Parser::parse(const QString& src) {
    QStringList tokens = split(src);
    if (tokens.isEmpty()) {
        return Command();
    }
    QString name = tokens.takeFirst();
    Command::Type type = Parser::type(name);
    return Command(type, name, tokens);
}

/*!
 * @brief コマンド文字列を受け取り、トークン単位で区切った文字列リストを返す。
 *
 * @param src コマンド文字列
 *
 * @return トークン単位で区切った文字列リスト
 */
QStringList cllaun::Parser::split(QString src) {
    QStringList tokens;
    QRegExp regex(COMMAND_TOKEN_REGEXP);

    int pos = 0;
    while ((pos = regex.indexIn(src, pos)) != -1) {
        QString token = regex.cap(0);
        token.replace("\\\"", "\"");
        tokens << token;
        pos += regex.matchedLength();
    }
    if (tokens.count() > 1) {
        for (int i = 1; i < tokens.size(); ++i) {
            QString arg = tokens.at(i);
            if (arg.startsWith('"') && arg.endsWith('"')) {
                tokens.replace(i, arg.mid(1, arg.size() - 2));
            }
        }
    }

    return tokens;
}

/*!
 * @brief トークンの Command::Type を返す。
 *
 * @param src トークン文字列
 *
 * @return 引数のトークンタイプ
 */
cllaun::Command::Type cllaun::Parser::type(const QString& src) {
    // case INVALID:
    if (src.isEmpty()) {
        return Command::INVALID;
    // case PLUGIN:
    } else if (src.startsWith(":")) {
        return Command::PLUGIN;
    // case PATH:
    } else if ((src.startsWith("\"") && src.endsWith("\"")) ||
               (src.indexOf(":") != -1) ||
               (src.indexOf("/") != -1)) {
        return Command::PATH;
    // case ALIAS:
    } else if (src.startsWith("?")) {
        return Command::ALIAS;
    // default:
    } else {
        return Command::ANY;
    }
}
