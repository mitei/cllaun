#pragma once

#include <QObject>
#include <QStringList>

namespace cllaun {

class Config : public QObject{
public:
    Config(QObject* parent = 0);

public slots:
    // 指定された設定ファイルを読み込む
    void Read(const QString& conf_name);
    //TODO: comment
    void AddSearchPath(const QString& dir_path);

private:
    static const char* extension;
    QStringList search_paths;
};

}
