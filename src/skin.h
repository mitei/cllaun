#pragma once

#include <QStringList>
#include <QObject>
#include <QScriptable>

class QApplication;

namespace cllaun {

class Skin : public QObject, public QScriptable {
    Q_OBJECT
public:
    static const char* skin_file_name; /*!< スキンファイルの名前 */

    // Skin スクリプトオブジェクトを生成
    static QScriptValue newQObject(QScriptEngine* engine, QApplication* _app);

public slots:
    // 指定されたスキンを読み込む
    void read(const QString& name);

private:
    Skin();
    Skin(QApplication* _app);

private:
    QApplication* app; /*!< スタイルシートを適用する対象となる QApplication */
};

}
