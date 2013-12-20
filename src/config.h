#pragma once

#include <QObject>
#include <QStringList>

namespace cllaun {

class Config : public QObject{
    Q_OBJECT
    Q_PROPERTY(QStringList dirs READ dirs WRITE setdirs)
public:
    Config(QObject* parent = nullptr);

    QStringList& dirs();
    void setdirs(const QStringList& dirs);

public slots:
    // 指定された設定ファイルを読み込む
    void read(const QString& conf_name);

private:
    static const char* extension;
    QStringList search_paths;
};

}
