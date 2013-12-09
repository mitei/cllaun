#include "parser_util.h"

std::vector<QString> ParserUtil::Tokenize(const QString& src)
{
    QString tmpSrc = src;
    const QStringList wordsList = tmpSrc.split( QRegExp(" (?=[^\"]*(\"[^\"]*\"[^\"]*)*$)") );
    std::vector<QString> ret;
    const QRegExp regexHasNotSpace("\\S+");
    foreach (const auto& word, wordsList)
    {
        if (word.isEmpty()) {
            continue; //連続空白があると空文字が混ざるので除去
        }
        ret.push_back(word);
    }
    return ret;
}
