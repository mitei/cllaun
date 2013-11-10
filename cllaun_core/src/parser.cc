#include "parser.h"
#include "command.h"

/*! パース実行(唯一の公開メソッド) */
Command Parser::Run(const QString& src)
{
    src;
    // 仮
    return Command(Command::INVALID, "", std::vector<QString>());
}

