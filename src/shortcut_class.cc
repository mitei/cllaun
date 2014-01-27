#include "shortcut_class.h"
#include <QScriptEngine>
#include <QShortcut>
#include "widget/widget.h"


Q_DECLARE_METATYPE(QKeySequence)

/*
 * -----
 * Class Shortcut
 * -----
 */

/*!
 * @brief コンストラクタ
 *
 * @param parent     親ウィジェット
 * @param _callback  ショートカット実行時のコールバック関数
 */
cllaun::Shortcut::Shortcut(QWidget* parent, const QScriptValue& _callback)
    : QObject(parent), shortcut(parent), callback(_callback)
{
    shortcut.setContext(Qt::WidgetWithChildrenShortcut);
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

/*!
 * @brief ショートカットのキーシーケンスを設定する
 *
 * @param key  変更後のキーシーケンス
 */
void cllaun::Shortcut::setKey(const QKeySequence& key) {
    shortcut.setKey(key);
}

/*!
 * @brief ショートカット実行時のコールバック関数を設定する
 *
 * @param _callback  ショートカット実行時のコールバック関数
 */
void cllaun::Shortcut::setCallback(const QScriptValue& _callback) {
    qScriptDisconnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
    callback = _callback;
    qScriptConnect(&shortcut, SIGNAL(activated()), QScriptValue(), callback);
}

/*!
 * @brief 関連付けられたキーシーケンスを取得する
 *
 * @return 関連付けられたキーシーケンス
 */
QKeySequence cllaun::Shortcut::getKeySequence() const {
    return shortcut.key();
}

/*!
 * @brief 関連付けられたコールバック関数を取得する
 *
 * @return 関連付けられたコールバック関数
 */
const QScriptValue& cllaun::Shortcut::getCallback() const {
    return callback;
}


/*
 * -----
 * Class Shortcuts
 * -----
 */

/*!
 * @brief デストラクタ
 */
cllaun::Shortcuts::~Shortcuts() {
    foreach (Shortcut* s, shortcuts) {
        delete s;
    }
}

/*!
 * @brief ショートカットを設定する
 *
 * @param key       ショートカットのキーシーケンス
 * @param callback  ショートカット実行時のコールバック関数
 */
void cllaun::Shortcuts::setShortcut(const QKeySequence& key, const QScriptValue& callback) {
    Shortcut* shortcut = getShortcut(key);
    if (shortcut == nullptr) {
        shortcut = new Shortcut(dynamic_cast<QWidget*>(parent()), callback);
        shortcut->setKey(key);
        shortcuts.push_back(shortcut);
        return;
    }
    shortcut->setCallback(callback);
}

/*!
 * @brief 指定されたキーシーケンスに関連付けられたショートカットを取得する
 *
 * @param key  取得したいショートカットに関連付けられたキーシーケンス
 * @return  指定されたキーシーケンスに関連付けられたショートカットまたは、
 *          それが無い場合 nullptr を返す
 */
cllaun::Shortcut* cllaun::Shortcuts::getShortcut(const QKeySequence& key) {
    foreach (Shortcut* s, shortcuts) {
        if (s->getKeySequence() == key) return s;
    }
    return nullptr;
}

/*!
 * @brief 指定されたキーシーケンスに関連付けられたショートカットを削除する
 *
 * @param key  削除したいショートカットに関連付けられたキーシーケンス
 */
void cllaun::Shortcuts::remove(const QKeySequence& key) {
    for (auto iter = shortcuts.begin(); iter != shortcuts.end(); ++iter) {
        Shortcut* s = (*iter);
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

cllaun::ShortcutClass::ShortcutClass(QScriptEngine* engine)
    : QObject(engine), QScriptClass(engine)
{
    qScriptRegisterMetaType(engine, keySequenceToScriptValue, keySequenceFromScriptValue);
}

QScriptValue::PropertyFlags cllaun::ShortcutClass::propertyFlags(
        const QScriptValue& object,
        const QScriptString& name,
        uint id)
{
    QKeySequence key(name.toString());
    // key が空文字の場合、指定された文字列はキーシーケンスではない。
    if (key.toString() == "") {
        return QScriptValue::SkipInEnumeration;
    }
    // ショートカットオブジェクトは通常の削除を禁止
    return QScriptValue::Undeletable;
}

QScriptClass::QueryFlags cllaun::ShortcutClass::queryProperty(
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

QScriptValue cllaun::ShortcutClass::property(
        const QScriptValue &object,
        const QScriptString& name,
        uint id)
{
    Shortcuts* shortcuts = qobject_cast<Shortcuts*>(object.data().toQObject());
    Shortcut* shortcut = shortcuts->getShortcut(QKeySequence(name.toString()));
    // 指定されたキーシーケンスのショートカットが存在しない場合、undefined を返す
    if (shortcut == nullptr) {
        return QScriptValue();
    } else {
        return engine()->newQObject(shortcut, QScriptEngine::QtOwnership);
    }
}

void cllaun::ShortcutClass::setProperty(
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

    Shortcuts* shortcuts = qobject_cast<Shortcuts*>(object.data().toQObject());
    QKeySequence key(name);
    // 右辺値が null の場合、指定されたキーシーケンスのショートカットを削除する。
    if (value.isNull()) {
        shortcuts->remove(key);
    } else {
        shortcuts->setShortcut(key, value);
    }
}


/*
 * QKeySequence の C++ / Qt Script 間の変換関数
 */
QScriptValue cllaun::ShortcutClass::keySequenceToScriptValue(
        QScriptEngine *engine, const QKeySequence &keyseq)
{
    return QScriptValue(keyseq.toString());
}

void cllaun::ShortcutClass::keySequenceFromScriptValue(
        const QScriptValue &obj, QKeySequence &keyseq)
{
    keyseq = QKeySequence(obj.toString());
}
