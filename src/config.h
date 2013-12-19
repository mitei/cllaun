#pragma once

#include <QObject>
#include <QStringList>

namespace cllaun {

class Config : public QObject{
    Q_OBJECT
public:
    Config(QObject* parent = nullptr);

public slots:
    // 指定された設定ファイルを読み込む
    void read(const QString& conf_name);
    //TODO: comment
    void addSearchPath(const QString& dir_path);

private:
    static const char* extension;
    QStringList search_paths;
};

}
