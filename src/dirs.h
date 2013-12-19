#pragma once

#include <QStringList>
#include <QDir>

class QString;

namespace cllaun {

/*!
 * @brief QDir をまとめたようなもの
 */
class Dirs {
public:
    Dirs();
    Dirs(const QStringList& _dirs);

    // ファイルの存在チェック
    bool exists(const QString& name) const;
    // 指定したファイルのパスを取得
    QString filePath(const QString& name) const;
    // 指定したディレクトリのパスを取得
    QString dirPath(const QString& name) const;
    // 指定したファイルまたはディレクトリのパスを取得
    QString path(const QString& name) const;
    // 条件にマッチするエントリのリストを取得
    QStringList entryList(
            const QStringList& name_filters,
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;
    // 条件にマッチするエントリのリストを取得
    QStringList entryList(
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;

    // ディレクトリの一覧に追加
    void append(const QString& value) { dirs << value; }
    // ディレクトリの一覧に追加
    Dirs& operator<<(const QString& value) { dirs << value; return *this; }
private:
    QStringList dirs;
};

}
