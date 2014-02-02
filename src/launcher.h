#pragma once

#include <QObject>
#include <QScriptable>
#include "command.h"
class QStringList;

namespace cllaun {

class Launcher : public QObject, public QScriptable {
    Q_OBJECT
public:
    // Launcher スクリプトオブジェクトを生成
    static QScriptValue newQObject(QScriptEngine* engine);

public slots:
    // コマンドを実行
    int run(QObject* command);
    // ファイルを開く
    //int execute(const QString& path, const QString& args);
    // 候補リストを取得
    QStringList list(const QString& src);

private:
    Launcher() { }
    // 指定された Command オブジェクトのコマンド名を正規化
    QString normalize(const Command& command);
    // 指定された文字列をコマンド名として解釈し、正規化
    QString normalize(const QString& name);
    // 指定されたコマンドタイプのコマンド名を正規化
    QString normalize(Command::Type type, const QString& name);
    // 指定されたコマンドタイプの候補リストを取得
    QStringList list(Command::Type type, const QString& name);
};

}
