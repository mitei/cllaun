#include "global_shortcut_class.h"
#include <QScriptEngine>
#include <QKeySequence>


/*
 * -----
 * Class GlobalShortcut
 * -----
 */

/*!
 * @brief コンストラクタ
 *
 * @param parent     親オブジェクト
 * @param _callback  ショートカットの実行時に呼ばれる関数
 */
cllaun::GlobalShortcut::GlobalShortcut(QObject* parent, const QScriptValue& _callback)
    : QObject(parent), shortcut(this), callback(_callback)
{
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

/*!
 * @brief ショートカットのキーシーケンスを設定
 *
 * @param key  キーシーケンス
 */
void cllaun::GlobalShortcut::setKey(const QKeySequence& key) {
    shortcut.setKey(key);
}

/*!
 * @brief ショートカット実行時のコールバック関数を設定
 *
 * @param _callback  ショートカット実行時のコールバック関数
 */
void cllaun::GlobalShortcut::setCallback(const QScriptValue& _callback) {
    qScriptDisconnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
    callback = _callback;
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

/*!
 * @brief 設定されているキーシーケンスを取得
 *
 * @return 設定されているキーシーケンス
 */
QKeySequence cllaun::GlobalShortcut::getKeySequence() const {
    return shortcut.key();
}

/*!
 * @brief 設定されているコールバック関数を取得
 *
 * @return 設定されているコールバック関数
 */
const QScriptValue& cllaun::GlobalShortcut::getCallback() const {
    return callback;
}


/*
 * -----
 * Class GlobalShortcuts
 * -----
 */

/*!
 * @brief デストラクタ
 */
cllaun::GlobalShortcuts::~GlobalShortcuts() {
    foreach (GlobalShortcut* s, shortcuts) {
        delete s;
    }
}

/*!
 * @brief ショートカットを設定する
 *
 * @param key       ショートカットのキーシーケンス
 * @param callback  ショートカット実行時のコールバック関数
 */
void cllaun::GlobalShortcuts::setShortcut(const QKeySequence& key, const QScriptValue& callback) {
    GlobalShortcut* shortcut = getShortcut(key);
    if (shortcut == nullptr) {
        shortcut = new GlobalShortcut(this, callback);
        shortcut->setKey(key);
        shortcuts.push_back(shortcut);
        return;
    }
    shortcut->setCallback(callback);
}

/*!
 * @brief 指定されたキーシーケンスに関連付けられた GlobalShortcut オブジェクトを取得
 *
 * @param key  取得したい GlobalShortcut に関連付けられたキーシーケンス
 * @return     指定されたキーシーケンスに関連付けられた GlobalShortcut* または、指定されたキーシーケンスに
 *             関連付けられた GlobalShortcut が存在しない場合、nullptr
 */
cllaun::GlobalShortcut* cllaun::GlobalShortcuts::getShortcut(const QKeySequence& key) {
    foreach (GlobalShortcut* s, shortcuts) {
        if (s->getKeySequence() == key) return s;
    }
    return nullptr;
}

/*!
 * @brief 指定されたキーシーケンスに関連付けられた GlobalShortcut を削除する
 *
 * @param key  削除したいショートカットのキーシーケンス
 */
void cllaun::GlobalShortcuts::remove(const QKeySequence& key) {
    for (auto iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        GlobalShortcut* s = (*iter);
        if (s->getKeySequence() == key) {
            delete s;
            shortcuts.erase(iter);
            return;
        }
    }
}


/*
 * -----
 * Class ShortcutClass
 * -----
 */

cllaun::GlobalShortcutClass::GlobalShortcutClass(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
}

QScriptValue::PropertyFlags cllaun::GlobalShortcutClass::propertyFlags(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    QKeySequence key(name.toString());
    // key が空文字の場合、指定された文字列はキーシーケンスではない。
    if (key.toString() == "") {
        return QScriptValue::SkipInEnumeration;
    }
    // ショートカットオブジェクトは通常の delete は不可
    return QScriptValue::Undeletable;
}

QScriptClass::QueryFlags cllaun::GlobalShortcutClass::queryProperty(
        const QScriptValue& object,
        const QScriptString& name,
        QueryFlags flags,
        uint* id)
{
    QKeySequence key(name.toString());
    // key が空文字の場合、指定された文字列はキーシーケンスではない。
    // この場合、QScriptClass で処理せず、Qt Script Object 型の通常のプロパティアクセスを行う。
    if (key.toString() == "") {
        return 0;
    }
    return flags;
}

QScriptValue cllaun::GlobalShortcutClass::property(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    GlobalShortcuts* shortcuts = qobject_cast<GlobalShortcuts*>(object.data().toQObject());
    GlobalShortcut* shortcut = shortcuts->getShortcut(QKeySequence(name.toString()));
    // 指定されたキーシーケンスのショートカットが存在しない場合、undefined を返す
    if (shortcut == nullptr) {
        return QScriptValue();
    } else {
        return engine()->newQObject(shortcut, QScriptEngine::QtOwnership);
    }
}

void cllaun::GlobalShortcutClass::setProperty(
        QScriptValue& object,
        const QScriptString& name,
        uint id,
        const QScriptValue& value)
{
    if (!value.isNull() && !value.isFunction()) {
        object.engine()->currentContext()->throwError(
                QScriptContext::TypeError, "Argument Error: Right-hand value must be a function or null.");
        return;
    }

    GlobalShortcuts* shortcuts = qobject_cast<GlobalShortcuts*>(object.data().toQObject());
    QKeySequence key(name);
    // 右辺値が null の場合、指定されたキーシーケンスのショートカットを削除する。
    if (value.isNull()) {
        shortcuts->remove(key);
    } else {
        shortcuts->setShortcut(key, value);
    }
}
