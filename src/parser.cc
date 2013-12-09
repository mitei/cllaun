#include "parser.h"
#include "parser_util.h"
#include "command.h"
#include "parser_util.h"
#include "lib/container_make.h"

/*! パース実行(唯一の公開メソッド) */
Command Parser::Run(const QString& src)
{
    const auto tokens = ParserUtil::Tokenize(src);
    std::vector<QString> args;
    if (tokens.empty())
    {
        return Command(Command::INVALID, "", args);
    }
    //-コマンドの種類を判別
    int cmdType = Command::INVALID;
    QString cmd = tokens[0];
    //--プラグイン：コロンで始まっている
    if (cmd.startsWith(":")) {
        cmdType = Command::PLUGIN;
        cmd = cmd.mid(1);
    }
    //--パス：ダブルクォートされている
    else
    if (cmd.startsWith("\"") && cmd.endsWith("\"")) {
        cmdType = Command::PATH;
        cmd = cmd.mid(1,cmd.length() - 2);
    }
    //--パス：途中にコロンを含む
    else
    if (cmd.indexOf(":") != -1) {
        cmdType = Command::PATH;
    }
    //--エイリアス：?から始まっている
    else
    if (cmd.startsWith("?")) {
        cmdType = Command::ALIAS;
        cmd = cmd.mid(1);
    }
    //--特定できない場合
    else {
        cmdType = Command::ANY;
    }

    //-パラメータ取り出し
    for (size_t i = 1 ; i < tokens.size(); ++i)
    {
        args.push_back(tokens[i]);
    }

    return Command(static_cast<Command::Type>(cmdType), cmd, args);
}

