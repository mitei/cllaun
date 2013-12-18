#pragma once

#include "dirs.h"

class QString;
class QApplication;

namespace cllaun {

class Skin {
public:
    static const char* skin_file_name; /*!< スキンファイルの名前 */

public:
    Skin(QApplication* _app);
    // 指定されたスキンを読み込む
    void Read(const QString& name);
    // スキンの検索パスを追加する
    void AddSearchPath(const QDir& dir) { search_paths << dir; }

private:
    Skin();

private:
    QApplication* app; /*!< スタイルシートを適用する対象となる QApplication */
    Dirs search_paths; /*!< スキン検索ディレクトリ一覧 */
};

}
