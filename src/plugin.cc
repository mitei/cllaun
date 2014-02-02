#include "plugin.h"
#include <QScriptEngine>


cllaun::Plugin::Plugin(QObject* parent)
    : QObject(parent)
{

}

/*!
 * @brief Plugin のインスタンスを生成し、JavaScript Object 化して返す
 *
 * プロパティに JavaScript Array を持つため通常のコンストラクタでは十分ではない。
 *
 * @param engine  スクリプトエンジン
 * @return Plugin のインスタンスの JavaScript オブジェクト
 */
QScriptValue cllaun::Plugin::newQObject(QScriptEngine* engine) {
    Plugin* plugin = new Plugin(engine);
    QScriptValue plugin_obj = engine->newQObject(plugin, QScriptEngine::AutoOwnership);
    plugin_obj.setProperty("ignore", engine->newArray(), QScriptValue::Undeletable);
    return plugin_obj;
}

/*!
 * @brief 読み込み済みプラグインのリストを返す
 *
 * @return 読み込み済みプラグインのリスト
 */
QStringList cllaun::Plugin::imported() const {
    return engine()->importedExtensions();
}

/*!
 * @brief 読み込み可能プラグインのリストを返す
 *
 * @return 読み込み可能プラグインのリスト
 */
QStringList cllaun::Plugin::available() const {
    return engine()->availableExtensions();
}

/*!
 * @brief 指定された名前のプラグインを読み込む
 *
 * @param name  読み込みたいプラグイン名
 */
void cllaun::Plugin::imports(const QString& name) const {
    QScriptValue result = engine()->importExtension(name);
    // スクリプトの読み込み時にエラーが発生した場合、エラーオブジェクトが返る。
    // そうでない場合、undefined が返る。
    if (!result.isUndefined()) {
        // TODO: Error
        //context()->throwError(QScriptContext::TypeError, result.toString());
    }
}

/*!
 * @brief すべてのプラグインを読み込む
 *
 * plugin.ignore で除外されたものを除くすべての読み込み可能プラグインを読み込む。
 */
void cllaun::Plugin::importAll() const {
    QStringList ignore_list = qscriptvalue_cast<QStringList>(thisObject().property("ignore"));
    QStringList available_list = engine()->availableExtensions();
    foreach (const QString name, available_list) {
        if (!ignore_list.contains(name))
            engine()->importExtension(name);
    }
}
