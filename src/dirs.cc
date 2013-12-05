#include <QString>
#include <QStringList>

#include "dirs.h"

cllaun::Dirs::Dirs() {
}

cllaun::Dirs::Dirs(const QList<QDir> &_dirs): dirs(_dirs) {
}

/*!
 * @brief 指定されたファイルの存在チェック
 *
 * 登録されているディレクトリの一覧からファイルを検索し、
 * 存在すれば true, 存在しなければ false を返す
 *
 * @param name ファイル名
 *
 * @return 存在すれば true, 存在しなければ false
 */
bool cllaun::Dirs::Exists(const QString& name) const {
    foreach (QDir dir, dirs) {
        if (dir.exists(name)) return true;
    }
    return false;
}

/*!
 * @brief 指定されたファイルのパスを取得する
 *
 * 登録されているディレクトリの一覧からファイルを検索し、
 * 最初に見つけたファイルの絶対パスを返す。
 * 見つからなかった場合は空の QString を返す。
 *
 * @param name ファイル名
 *
 * @return 最初に見つかったファイルの絶対パスまたは空文字列。
 */
QString cllaun::Dirs::FilePath(const QString &name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Files|QDir::Hidden;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = EntryList(name_filters, filters, sort_flags);
    return (entry_list.isEmpty() ? QString() : entry_list.at(0) );
}

/*!
 * @brief 指定されたディレクトリのパスを取得する
 *
 * 登録されているディレクトリの一覧からディレクトリを検索し、
 * 最初に見つけたディレクトリの絶対パスを返す。
 * 見つからなかった場合は空の QString を返す。
 *
 * @param name ディレクトリ名
 *
 * @return 最初に見つかったディレクトリの絶対パスまたは空文字列。
 */
QString cllaun::Dirs::DirPath(const QString &name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = EntryList(name_filters, filters, sort_flags);
    return (entry_list.isEmpty() ? QString() : entry_list.at(0) );
}

/*!
 * @brief 指定されたファイルまたはディレクトリのパスを取得する
 *
 * 登録されているディレクトリの一覧から検索し、
 * 最初に見つけたファイルまたはディレクトリの絶対パスを返す。
 * 見つからなかった場合は空の QString を返す。
 *
 * @param name ファイル名またはディレクトリ名
 *
 * @return 最初に見つかったファイルまたはディレクトリの絶対パスまたは空文字列。
 */
QString cllaun::Dirs::Path(const QString &name) const {
    foreach (QDir dir, dirs) {
        if (dir.exists(name))
            return dir.absolutePath() + QDir::separator() + name;
    }
    return QString();
}

/*!
 * @brief 指定した条件にマッチするファイルのリストを取得する
 *
 * @param name_filters 検索するエントリ名のリスト。ワイルドカード * ? を使用することが出来る。
 * @param filters      QDir::Filter を参照。エントリの種類（ファイル、ディレクトリ、隠しファイルなど）を指定できる。
 * @param sort         QDir::SortFlag を参照。ソート方法を指定出来る。
 *
 * @return マッチしたエントリのリスト
 */
QStringList cllaun::Dirs::EntryList(const QStringList &name_filters, QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (QDir dir, dirs) {
        // TODO: ディレクトリがソートされていない
        QStringList entry_list =  dir.entryList(name_filters, filters, sort);
        QString dirpath = dir.absolutePath();
        foreach (QString name, entry_list) {
            all_entry_list << (dirpath + QDir::separator() + name);
        }
    }
    return all_entry_list;
}

/*!
 * @brief 指定した条件にマッチするファイルのリストを取得する
 *
 * @param filters      QDir::Filter を参照。エントリの種類（ファイル、ディレクトリ、隠しファイルなど）を指定できる。
 * @param sort         QDir::SortFlag を参照。ソート方法を指定出来る。
 *
 * @return マッチしたエントリのリスト
 */
QStringList cllaun::Dirs::EntryList(QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (QDir dir, dirs) {
        // TODO: ディレクトリがソートされていない
        QStringList entry_list =  dir.entryList(filters, sort);
        foreach (QString name, entry_list) {
            all_entry_list << (dir.absolutePath() + QDir::separator() + name);
        }
    }
    return all_entry_list;
}
