#include <QString>
#include <QtTest>

#include <src/parser_util.h>

// unit test of parser
class Unit_parserutilTest : public QObject
{
    Q_OBJECT

public:
    Unit_parserutilTest();

private Q_SLOTS:
    void testPluginCmd_standard();
};

Unit_parserutilTest::Unit_parserutilTest()
{
}

void Unit_parserutilTest::testPluginCmd_standard()
{
    const QString trg = "hoge fuga";
    auto result = ParserUtil::Split(trg);
    QCOMPARE("hoge", result[0]);
    QCOMPARE("hoge", result[1]);
}

QTEST_APPLESS_MAIN(Unit_parserutilTest)

#include "tst_unit_parserutiltest.moc"

