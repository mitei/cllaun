#pragma once

#include <QStringList>

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
    void AddSearchPath(const QString& dir_path) { search_paths << dir_path; }

private:
    Skin();

private:
    QApplication* app; /*!< スタイルシートを適用する対象となる QApplication */
    QStringList search_paths; /*!< スキン検索ディレクトリ一覧 */
};

}
