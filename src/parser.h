﻿#pragma once

class QString;
class QStringList;

/*! @class Parser
    @brief 
*/

namespace cllaun {

class Command;

class Parser
{
public:
    /*! パース実行(唯一の公開メソッド) 
     *  @param[in] src パース対象文字列(ランチャに入力される生テキスト)
     *  @return コマンド候補リスト
     *  @note
     *      単純にユーザの入力テキストを受け取り、Command候補リストを返す。
     *      Commandには詳細なエラー情報を保持する能力は無いので、パースエラーが発生した
     *      場合には、単に空のリストを返す。
     *
     *      エラーとして想定しているのは次のようなもの。
     *      - 空文字列
     *      - 禁止文字(行頭禁止を含む)を含んでいる文字列
     *
     *      次のようなものはパース時点ではエラーとはしない。
     *      - 未登録のコマンド
     *      - 存在しないパス
     *
    */
    static Command parse(const QString& src);
    static QStringList split(QString src);

private:
    Parser();
    // utilities for parsing
};

}
