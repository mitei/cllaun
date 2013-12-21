#pragma once

#include <QObject>
#include <QStringList>

class QScriptEngine;

namespace cllaun {

class Config : public QObject{
    Q_OBJECT
    Q_PROPERTY(QStringList dirs READ dirs WRITE setdirs)

public:
    Config(QScriptEngine* _engine, QObject* parent = nullptr);

    QStringList& dirs();
    void setdirs(const QStringList& dirs);

public slots:
    // 指定された設定ファイルを読み込む
    void read(const QString& conf_name);

private:
    Config();
    static const char* extension;
    QScriptEngine* engine;
    QStringList search_paths;
};

}
