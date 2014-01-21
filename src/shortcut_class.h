#pragma once

#include <QObject>
#include <QWidget>
#include <QScriptClass>
#include <QScriptValue>
#include <QScriptable>
#include <QList>
#include <QShortcut>
#include <QKeySequence>
class QScriptEngine;
class QScriptContext;

namespace cllaun {

/*
 * -----
 * Class Shortcut
 * -----
 */
/*!
 * @class Shortcut
 * @brief ショートカット。
 *
 * コールバックとキーシーケンスの関連付けやスクリプトからの READ アクセスのために必要
 */
class Shortcut : public QObject {
    Q_OBJECT
    Q_PROPERTY(QKeySequence key READ getKeySequence)
    Q_PROPERTY(QScriptValue value READ getCallback)

public:
    Shortcut(QWidget* parent, const QScriptValue& _callback);
    // キーシーケンスを設定
    void setKey(const QKeySequence& key);
    // コールバック関数を設定
    void setCallback(const QScriptValue& _callback);
    /* property */
    QKeySequence getKeySequence() const;
    const QScriptValue& getCallback() const;

private:
    QShortcut shortcut; /*!< ショートカット */
    QScriptValue callback; /*!< コールバック関数 */
};

/*
 * -----
 * Class Shortcuts
 * -----
 */
/*!
 * @class Shortcuts
 * @brief  ShortcutClass のインスタンス本体。
 */
class Shortcuts : public QObject {
    Q_OBJECT
public:
    Shortcuts(QWidget* _parent)
        : QObject(_parent) { }
    ~Shortcuts();

    // 指定されたキーシーケンスのショートカットを取得する
    Shortcut* getShortcut(const QKeySequence& key);
    // ショートカットを設定する
    void setShortcut(const QKeySequence& key, const QScriptValue& callback);
    // 指定されたキーシーケンスのショートカットを削除する
    void remove(const QKeySequence& key);

private:
    QList<Shortcut*> shortcuts; /*!< ショートカットのリスト */
};

/*
 * -----
 * Class ShortcutClass
 * -----
 */
/*!
 * @class ShortcutClass
 * @brief ショートカットに独自のプロパティアクセス手段を提供するクラス
 */
class ShortcutClass : public QObject, public QScriptClass {
public:
    ShortcutClass(QScriptEngine* engine);

    /*
     * QScriptClass の再実装のみなのでコメント省略
     */
    QString name() const { return QString("Shortcut"); }

    QScriptValue::PropertyFlags propertyFlags(const QScriptValue& object,
                                              const QScriptString& name,
                                              uint id);
    QueryFlags queryProperty(const QScriptValue& object,
                               const QScriptString& name,
                               QueryFlags flags,
                               uint* id);
    QScriptValue property(const QScriptValue& object,
                          const QScriptString& name,
                          uint id);
    void setProperty(QScriptValue& object,
                     const QScriptString& name,
                     uint id,
                     const QScriptValue& value);

private:
    /*
     * QKeySequence の C++ / Qt Script 間の変換関数
     */
    static QScriptValue keySequenceToScriptValue(QScriptEngine* engine, const QKeySequence& keyseq);
    static void keySequenceFromScriptValue(const QScriptValue& obj, QKeySequence& keyseq);
};

}
