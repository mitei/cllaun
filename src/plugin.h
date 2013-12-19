#pragma once

#include <QStringList>
#include <QObject>

class QString;

namespace cllaun {

class Plugin : public QObject {
    Q_OBJECT
public:
    Plugin(QObject* parent = nullptr);
    // 指定されたプラグインを読み込む
    void read(const QString& name);
    // すべてのプラグインを読み込む
    void readAll();
    // 読み込み済みプラグインの一覧
    inline const QStringList& loadedPlugin() { return loaded_plugin; }
    // プラグインを検索するディレクトリを追加
    inline void addDir(const QString& dir_path) { search_paths << dir_path; }

private:
    // 内部用、プラグイン読み込み
    void load(const QString& path);

private:
    static const char* extension;   /*!< プラグインの拡張子 */
    QStringList loaded_plugin;      /*!< 読み込み済みのプラグイン一覧 */
    QStringList search_paths;              /*!< プラグイン検索ディレクトリの一覧 */
};

}
