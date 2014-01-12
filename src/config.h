#pragma once

#include <QObject>
#include <QScriptable>
#include <QStringList>

class QScriptEngine;

namespace cllaun {

class Config : public QObject, public QScriptable {
    Q_OBJECT

public:
    // Config スクリプトオブジェクトを生成
    static QScriptValue newQObject(QScriptEngine* engine);

public slots:
    // 設定ファイルを読み込む
    void read();

private:
    Config();
    static QStringList file_list;
};

}
