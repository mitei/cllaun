#include "parser.h"
#include "command.h"

/*! パース実行(唯一の公開メソッド) */
Command Parser::Run(const QString& src)
{
    src;
    // 仮
    std::vector<QString> args;
    args.push_back("arg1");
    args.push_back("arg2");
    return Command(Command::PLUGIN_CMD, "hoge", args);
}

