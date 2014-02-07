#pragma once

#include <QObject>
#include <QList>
#include <QScriptClass>
#ifdef Q_OS_WIN32
#include "qglobalshortcut.h"
#else
#include <QxtWidgets/QxtGlobalShortcut>
typedef QxtGlobalShortcut QGlobalShortcut;
#endif

namespace cllaun {
/*
 * -----
 * Class GlobalShortcut
 * -----
 */
/*!
 * @class GlobalShortcut
 * @brief  グローバルショートカット。
 *
 * コールバックとキーシーケンスの関連付けやスクリプトからの READ アクセスのために必要
 */
class GlobalShortcut : public QObject {
    Q_OBJECT
    Q_PROPERTY(QKeySequence key READ getKeySequence)
    Q_PROPERTY(QScriptValue value READ getCallback)

public:
    GlobalShortcut(QObject* parent, const QScriptValue& _callback);
    // キーシーケンスを設定
    void setKey(const QKeySequence& key);
    // コールバックを設定
    void setCallback(const QScriptValue& _callback);
    /* property */
    QKeySequence getKeySequence() const;
    const QScriptValue& getCallback() const;

private:
    QGlobalShortcut shortcut; /*!< ショートカットオブジェクト */
    QScriptValue callback; /*!< ショートカット実行時に呼ばれるコールバック関数 */
};

/*
 * -----
 * Class GlobalShortcuts
 * -----
 */
/*!
 * @class GlobalShortcuts
 * @brief  GlobalShortcutClass のインスタンス本体。
 */
class GlobalShortcuts : public QObject {
    Q_OBJECT
public:
    GlobalShortcuts(QObject* _parent)
        : QObject(_parent) { }
    ~GlobalShortcuts();

    // 指定されたキーシーケンスに関連付けられたショートカットを取得する
    GlobalShortcut* getShortcut(const QKeySequence& key);
    // ショートカットを設定する
    void setShortcut(const QKeySequence& key, const QScriptValue& callback);
    // 指定されたキーシーケンスに関連付けられたショートカットを削除する
    void remove(const QKeySequence& key);

private:
    QList<GlobalShortcut*> shortcuts; /*!< ショートカットのリスト */
};

/*
 * -----
 * Class GlobalShortcutClass
 * -----
 */
/*!
 * @class GlobalShortcutClass
 * @brief グローバルショートカットに独自のプロパティアクセス手段を提供するクラス
 */
class GlobalShortcutClass : public QObject, public QScriptClass {
public:
    GlobalShortcutClass(QScriptEngine* engine);

    /*
     * QScriptClass の再実装のみなのでコメントは省略
     */
    QString name() const { return QString("GlobalShortcut"); }

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
};

}
