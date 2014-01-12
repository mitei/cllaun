#include "dirs.h"

#include <QString>
#include <QStringList>


cllaun::Dirs::Dirs() {
}

cllaun::Dirs::Dirs(const QStringList& _dirs): dirs(_dirs) {
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
bool cllaun::Dirs::exists(const QString& name) const {
    foreach (const QString& dir_path, dirs) {
        QDir dir(dir_path);
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
QString cllaun::Dirs::filePath(const QString& name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Files|QDir::Hidden;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = entryList(name_filters, filters, sort_flags);
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
QString cllaun::Dirs::dirPath(const QString& name) const {
    QStringList name_filters(name);
    QDir::Filters filters = QDir::Dirs|QDir::NoDotAndDotDot;
    QDir::SortFlags sort_flags = QDir::Name;

    QStringList entry_list = entryList(name_filters, filters, sort_flags);
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
QString cllaun::Dirs::path(const QString& name) const {
    foreach (const QString& dir_path, dirs) {
        QDir dir(dir_path);
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
QStringList cllaun::Dirs::entryList(const QStringList& name_filters, QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (const QString& dir_path, dirs) {
        QDir dir(dir_path);
        // TODO: ディレクトリがソートされていない
        QStringList entry_list =  dir.entryList(name_filters, filters, sort);
        foreach (const QString& name, entry_list) {
            all_entry_list << (QDir::toNativeSeparators(dir.absolutePath() + '/' + name));
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
QStringList cllaun::Dirs::entryList(QDir::Filters filters, QDir::SortFlags sort) const {
    QStringList all_entry_list;
    foreach (const QString& dir_path, dirs) {
        QDir dir(dir_path);
        // TODO: ディレクトリがソートされていない
        QStringList entry_list =  dir.entryList(filters, sort);
        foreach (const QString& name, entry_list) {
            all_entry_list << (QDir::toNativeSeparators(dir.absolutePath() + '/' + name));
        }
    }
    return all_entry_list;
}
