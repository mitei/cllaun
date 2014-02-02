#pragma once

#include <QObject>
#include <QScriptable>
#include <QStringList>
class QScriptEngine;
class QScriptValue;

namespace cllaun {

/*!
 * @class Plugin
 * @brief プラグインの読み込みなどを行う
 */
class Plugin : public QObject, public QScriptable {
    Q_OBJECT
    Q_PROPERTY(QStringList imported READ imported)
    Q_PROPERTY(QStringList available READ available)

public:
    // Plugin のインスタンスの JavaScript Object を生成する
    static QScriptValue newQObject(QScriptEngine* engine);
    /* property */
    QStringList imported() const;
    QStringList available() const;

public slots:
    // 指定された名前のプラグインを読み込む
    void imports(const QString& name) const;
    // すべてのプラグインを読み込む
    void importAll() const;

private:
    // 常に Plugin は thisObject を持つ必要があるため、通常のコンストラクタ呼び出しを禁止する。
    Plugin(QObject* parent);
};

}
