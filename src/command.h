#pragma once

#include <vector>
#include <QString>

/*! @struct Command
    @brief 
        コマンドを表現するための構造体。
        パーサはユーザの入力したテキストを解析し、この構造体のオブジェクトを返す。
    @note
        - コマンド種類のバリエーションはこれで良いか？
        - パラメータは単純な文字列のリストで良いか？
        - パースの時点では、プラグインコマンドがシステム提供かユーザ提供か
          区別しない。
*/
struct Command
{
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
    Command(Type type, const QString& name, const std::vector<QString>& args)
        : type_(type), name_(name), args_(args)
    {}
    Command(Type type, const QString& name)
        : type_(type), name_(name)
    {}
    Command()
        : type_(INVALID)
    {}
public:
    Type                 type_;
    QString              name_; /*!< コマンド名(コロンは含まない)またはパス名 */
    std::vector<QString> args_; /*!< パラメータ(オプショナル) */
};

