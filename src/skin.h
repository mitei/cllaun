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

    QStringList& dirs();
    void setDirs(const QStringList& paths);

public slots:
    // 指定されたスキンを読み込む
    void read(const QString& name);

private:
    Skin();

private:
    QApplication* app; /*!< スタイルシートを適用する対象となる QApplication */
    QStringList search_paths; /*!< スキン検索ディレクトリ一覧 */
};

}
