#pragma once

#include <QStringList>
#include <QObject>

class QApplication;

namespace cllaun {

class Skin : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList dirs READ dirs WRITE setDirs)
public:
    static const char* skin_file_name; /*!< スキンファイルの名前 */

public:
    Skin(QApplication* _app, QObject* parent = nullptr);
    // 指定されたスキンを読み込む
    void read(const QString& name);
    // スキンの検索パスを追加する
    void addSearchPath(const QString& dir_path) { search_paths << dir_path; }

    QStringList& dirs();
    void setDirs(const QStringList& paths);

private:
    Skin();

private:
    QApplication* app; /*!< スタイルシートを適用する対象となる QApplication */
    QStringList search_paths; /*!< スキン検索ディレクトリ一覧 */
};

}
