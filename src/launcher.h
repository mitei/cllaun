#pragma once

#include <QObject>
#include <QScriptable>
#include <QStringList>

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
    // normalize command name
    QString normalize(const Command& command);
};

}
