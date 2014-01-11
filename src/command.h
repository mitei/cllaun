#pragma once

#include <QStringList>
#include <QString>

/*! @class Command
    @brief 
        コマンドを表現するための構造体。
        パーサはユーザの入力したテキストを解析し、この構造体のオブジェクトを返す。
    @note
        - コマンド種類のバリエーションはこれで良いか？
        - パラメータは単純な文字列のリストで良いか？
        - パースの時点では、プラグインコマンドがシステム提供かユーザ提供か
          区別しない。
*/

namespace cllaun {

class Command : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString type READ getTypeString)
    Q_PROPERTY(QString name READ getName)
    Q_PROPERTY(QStringList args READ getArgs)

public:
    /*! @enum Type
        @brief コマンド種類
    */
    enum Type
    {
        INVALID     = 0x00, /*!< 無効なコマンド */
        EXECUTABLE  = 0x01, /*!< Executable(パスの通った実行可能ファイル) */
        PLUGIN      = 0x02, /*!< プラグインコマンド */
        PATH        = 0x04, /*!< ファイル・ディレクトリパス(ファイラ) */
        ALIAS       = 0x08, /*!< エイリアス */

        ANY         = EXECUTABLE | PLUGIN | PATH | ALIAS /*!< 不明 */
    };

public:
    Command()
        : QObject(nullptr), type(INVALID)
    {}
    Command(Type _type, const QString& _name)
        : QObject(nullptr), type(_type), name(_name)
    {}
    Command(Type _type, const QString& _name, const QStringList& _args)
        : QObject(nullptr), type(_type), name(_name), args(_args)
    {}
    Command(const Command& rhs)
        : QObject(nullptr), type(rhs.type), name(rhs.name), args(rhs.args)
    {}

    const QString getTypeString() const;
    const Type getType() const { return type; }
    const QString& getName() const { return name; }
    const QStringList& getArgs() const { return args; }

private:
    const Type         type;
    const QString      name; /*!< コマンド名(コロンは含まない)またはパス名 */
    const QStringList  args; /*!< パラメータ(オプショナル) */
};

}
