#include <QString>
#include <QtTest>
#include <vector>

#include "../../src/lib/container_make.h"
#include "../../src/parser.h"
#include "../../src/command.h"
#include "../../src/parser_util.h"

// テストフレームワークで使うための下準備
Q_DECLARE_METATYPE(Command::Type)
Q_DECLARE_METATYPE(std::vector<QString>)

// unit test of parser
class Unit_parserTest : public QObject
{
    Q_OBJECT

public:
    Unit_parserTest() {}

private Q_SLOTS:
    void testParsePluginCmd_data();
    void testParsePluginCmd();
    void testSplitWords_data();
    void testSplitWords();
};

// パース：プラグインコマンド
void Unit_parserTest::testParsePluginCmd_data()
{
    QTest::addColumn<QString>("target" );
    QTest::addColumn<Command::Type       >("result_type"  );
    QTest::addColumn<QString             >("result_name"  );
    QTest::addColumn<std::vector<QString>>("result_params");

    // 引数なし
//    std::vector<QString> params1;
//    QTest::newRow("non-args") << ":hoge"
//        << Command::PLUGIN_CMD << "hoge" << params1;

    // 引数１個
//    std::vector<QString> params2;
//    params2.push_back("arg1");
//    QTest::newRow("single-arg") << ":fuga arg1"
//        << Command::PLUGIN_CMD << "fuga" << params2;

    // 引数が複数個
    const auto params3 = make_vector<QString>("arg1")("arg2")();
    QTest::newRow("multi-arg") << ":hoge arg1 arg2"
        << Command::PLUGIN_CMD << "hoge" << params3;
}
void Unit_parserTest::testParsePluginCmd()
{
    QFETCH(QString, target );
    QFETCH(Command::Type       , result_type  );
    QFETCH(QString             , result_name  );
    QFETCH(std::vector<QString>, result_params);

    const Command result = Parser::Run(target);

    QCOMPARE(result.type_, result_type);
    QCOMPARE(result.name_, result_name);
    QCOMPARE(result.params_.size(), result_params.size());
    if (result.params_.size() != result_params.size()) { return; }
    for(size_t i = 0; i < result_params.size(); ++i)
    {
        QCOMPARE(result.params_[i], result_params[i]);
    }
}

// 文字列分割
void Unit_parserTest::testSplitWords_data()
{
    QTest::addColumn<QString>("target" );
    QTest::addColumn<std::vector<QString>>("require");

    // シンプル１要素
//    std::vector<QString> res1;
//    res1.push_back("hoge");
//    QTest::newRow("simple-one-elm") << "hoge" << res1;

    // シンプル複数要素
    const auto res2 = make_vector<QString>("hoge")("fuga")();
    QTest::newRow("simple-multi-elms") << "hoge fuga" << res2;
}
void Unit_parserTest::testSplitWords()
{
    QFETCH(QString, target );
    QFETCH(std::vector<QString>, require);

    const auto result = ParserUtil::Split(target);

    QCOMPARE(result.size(), require.size());
    if (result.size() != require.size()) { return; }
    for(size_t i = 0; i < result.size(); ++i)
    {
        QCOMPARE(result[i], require[i]);
    }
}

QTEST_APPLESS_MAIN(Unit_parserTest)

#include "tst_unit_parsertest.moc"

