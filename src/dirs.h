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
    bool Exists(const QString& name) const;
    // 指定したファイルのパスを取得
    QString FilePath(const QString& name) const;
    // 指定したディレクトリのパスを取得
    QString DirPath(const QString& name) const;
    // 指定したファイルまたはディレクトリのパスを取得
    QString Path(const QString& name) const;
    // 条件にマッチするエントリのリストを取得
    QStringList EntryList(
            const QStringList& name_filters,
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;
    // 条件にマッチするエントリのリストを取得
    QStringList EntryList(
            QDir::Filters filters = QDir::NoFilter,
            QDir::SortFlags sort = QDir::NoSort) const;

    // ディレクトリの一覧に追加
    void Append(const QString& value) { dirs << value; }
    // ディレクトリの一覧に追加
    Dirs& operator<<(const QString& value) { dirs << value; return *this; }
private:
    QStringList dirs;
};

}
