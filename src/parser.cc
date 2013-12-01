#include "parser.h"
#include "command.h"
#include "parser_util.h"
#include "lib/container_make.h"

/*! パース実行(唯一の公開メソッド) */
std::vector<Command> Parser::Run(const QString& src)
{
    auto tokens = ParserUtil::Tokenize(src);
    // 仮
    std::vector<QString> args;
    args.push_back("arg1");
    args.push_back("arg2");
    return make_vector<Command>(Command(Command::PLUGIN_CMD, "hoge", args))();
}

