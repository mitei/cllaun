#include <QString>
#include <QtTest>
#include <vector>

#include "../../src/lib/container_make.h"
#include "../../src/parser.h"
#include "../../src/command.h"
#include "../../src/parser_util.h"

// テストフレームワークで使うための下準備
Q_DECLARE_METATYPE(Command)
Q_DECLARE_METATYPE(Command::Type)
Q_DECLARE_METATYPE(std::vector<QString>)

// unit test of parser
class Unit_parserTest : public QObject
{
    Q_OBJECT

public:
    Unit_parserTest() {}

private Q_SLOTS:
    void testTokenize_data();
    void testTokenize();
    void testParse_data();
    void testParse();
};

// 文字列分割
void Unit_parserTest::testTokenize_data()
{
    QTest::addColumn<QString>("target" );
    QTest::addColumn<std::vector<QString>>("require");

    // シンプル１要素
    std::vector<QString> resSimple;
    resSimple.push_back("hoge");
    QTest::newRow("シンプル１要素") << "hoge" << resSimple;

    // シンプル複数要素
    const auto resMultiElem = make_vector<QString>("hoge")("fuga")();
    QTest::newRow("シンプル複数要素") << "hoge fuga" << resMultiElem;

    // 連続空白
    const auto resMultiSpace = make_vector<QString>("hoge")("fuga")();
    QTest::newRow("連続空白") << "hoge     fuga" << resMultiSpace;

    // ダブルクォーテーション中のスペース
    const auto resDoubleQuote = make_vector<QString>("hoge")("\"fuga hogera\"")();
    QTest::newRow("ダブルクォーテーション中のスペース") << "hoge \"fuga hogera\"" << resDoubleQuote;
}
void Unit_parserTest::testTokenize()
{
    QFETCH(QString, target );
    QFETCH(std::vector<QString>, require);

    const auto result = ParserUtil::Tokenize(target);

    QCOMPARE(result.size(), require.size());
    if (result.size() != require.size()) { return; }
    for(size_t i = 0; i < result.size(); ++i)
    {
        QCOMPARE(result[i], require[i]);
    }
}

// パース
void Unit_parserTest::testParse_data()
{
    QTest::addColumn<QString>("target" );
    QTest::addColumn<Command>("expect"  );

    //-----------------------------
    // プラグインコマンド
    //-----------------------------
    {
        const std::vector<QString> args;
        QTest::newRow("プラグイン：引数なし") << ":hoge" << Command(Command::PLUGIN, "hoge", args);
    }
    {
        const std::vector<QString> args = make_vector<QString>("arg1")();
        QTest::newRow("プラグイン：引数1個") << ":fuga arg1" << Command(Command::PLUGIN, "fuga", args);
    }
    {
        const std::vector<QString> args = make_vector<QString>("arg1")("arg2")();
        QTest::newRow("プラグイン：引数が複数個") << ":hoge arg1 arg2" << Command(Command::PLUGIN, "hoge", args);
    }

    //-----------------------------
    // パス(コロン付き)
    //-----------------------------
    {
        const std::vector<QString> args;
        QTest::newRow("パス(コロン付き)：引数なし") << "D:/mydir" << Command(Command::PATH, "D:/mydir", args);
    }
    {
        const auto args = make_vector<QString>("arg1")("arg2")();
        QTest::newRow("パス(コロン付き)：引数があり") << "D:/mydir arg1 arg2" << Command(Command::PATH, "D:/mydir", args);
    }

    //-----------------------------
    // パス(ダブルクォート)
    //-----------------------------
    {
        const std::vector<QString> args;
        QTest::newRow("パス(ダブルクォート)：引数なし") << "\"file_on_cd\"" << Command(Command::PATH, "file_on_cd", args);
    }
    {
        const auto args = make_vector<QString>("arg1")("arg2")();
        QTest::newRow("パス(ダブルクォート)：引数があり") << "\"file_on_cd\" arg1 arg2" << Command(Command::PATH, "file_on_cd", args);
    }

    //-----------------------------
    // エイリアス
    //-----------------------------
    {
        const std::vector<QString> args;
        QTest::newRow("エイリアス：引数なし") << "?hoge" << Command(Command::ALIAS, "hoge", args);
    }
    {
        const std::vector<QString> args = make_vector<QString>("arg1")();
        QTest::newRow("エイリアス：引数1個") << "?fuga  arg1" << Command(Command::ALIAS, "fuga", args);
    }
    {
        const std::vector<QString> args = make_vector<QString>("arg1")("arg2")();
        QTest::newRow("エイリアス：引数が複数個") << "?hoge arg1 arg2" << Command(Command::ALIAS, "hoge", args);
    }
    
    //-----------------------------
    // 特定できない
    //-----------------------------
    {
        const std::vector<QString> args;
        QTest::newRow("特定できない：引数なし") << "hoge" << Command(Command::ANY, "hoge", args);;
    }
    {
        const std::vector<QString> args = make_vector<QString>("arg1")("arg2")();
        QTest::newRow("特定できない：引数あり") << "hoge arg1 arg2" << Command(Command::ANY, "hoge", args);;
    }


}

void Unit_parserTest::testParse()
{
    QFETCH(QString, target );
    QFETCH(Command, expect );

    const Command result = Parser::Run(target);

    QCOMPARE(expect.type_, result.type_);
    QCOMPARE(expect.name_, result.name_);
    QCOMPARE(expect.args_.size(), result.args_.size());
    for (size_t i = 0; i < expect.args_.size(); ++i)
    {
        QCOMPARE(expect.args_[i], result.args_[i]);
    }
}

QTEST_APPLESS_MAIN(Unit_parserTest)

#include "tst_unit_parsertest.moc"

