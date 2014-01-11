#pragma once

#include <QObject>
#include <QScriptable>

namespace cllaun {

class Command;

class Launcher : public QObject, public QScriptable {
    Q_OBJECT
public:
    static QScriptValue newQObject(QScriptEngine* engine);

public slots:
    // コマンドを実行
    int run(QObject* command);
    // ファイルを開く
    int execute(const QString& path, const QString& args);

private:
    Launcher() { }
};

}
