#include <QString>
#include <QtTest>

#include "src/parser.h"
#include "src/command.h"
#include "src/parser_util.h"

// unit test of parser
class Unit_parserTest : public QObject
{
    Q_OBJECT

public:
    Unit_parserTest();

private Q_SLOTS:
    void testPluginCmd_standard();
    void testSplit_standard();
};

Unit_parserTest::Unit_parserTest()
{
}

void Unit_parserTest::testPluginCmd_standard()
{
    const QString somePluginCmd = "hoge";
    const QString someArg1 = "arg1";
    const QString someArg2 = "arg2";
    const auto cmd = Parser::Run(":" + somePluginCmd + " " + someArg1 + " " + someArg2);

    QCOMPARE(cmd.type_, Command::PLUGIN_CMD);
    QCOMPARE(cmd.name_, somePluginCmd);
    QCOMPARE(cmd.params_.size(), (size_t)2);
    QCOMPARE(cmd.params_[0], someArg1);
    QCOMPARE(cmd.params_[1], someArg2);
}

void Unit_parserTest::testSplit_standard()
{
    const QString trg = "hoge fuga";
    auto result = ParserUtil::Split(trg);
    QCOMPARE(QString("hoge"), result[0]);
    QCOMPARE(QString("fuga"), result[1]);
}

QTEST_APPLESS_MAIN(Unit_parserTest)

#include "tst_unit_parsertest.moc"
