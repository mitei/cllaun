#ifndef CORE_COMMAND_H
#define CORE_COMMAND_H

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
        EXECUTABLE  , /*!< Executable(パスの通った実行可能ファイル) */
        PLUGIN_CMD  , /*!< プラグインコマンド */
        PATH        , /*!< ファイル・ディレクトリパス(ファイラ) */
        ALIAS       , /*!< エイリアス */
        INVALID       /*!< 無効なコマンド */
    };
public:
    Command(Type type, const QString& name, const std::vector<QString>& params)
        : type_(type), name_(name), params_(params)
    {}
    Command(Type type, const QString& name)
        : type_(type), name_(name)
    {}
public:
    Type                 type_  ;
    QString              name_  ; /*!< コマンド名(コロンは含まない)またはパス名 */
    std::vector<QString> parmas_; /*!< パラメータ(オプショナル) */
};

#endif // CORE_COMMAND_H

