#include "api.h"
#include "plugin.h"
#include "native_plugin.h"

#include "api_plugin.h"

/*!
 * @brief 他の JavaScript ファイルを読み込む
 *
 * @return undefined
 */
static QScriptValue Require(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

/*!
 * @brief 他の JavaScript ファイルを読み込む
 *
 * @return undefined
 */
static QScriptValue Include(QScriptContext* context, QScriptEngine* engine) {
    return QScriptValue::UndefinedValue;
}

/*!
 * @brief Plugin 関連 API の初期化
 */
void cllaun::InitPlugin() {
    /*
    QScriptEngine* engine = cllaun::Core::Engine();
    engine->globalObject().setProperty("plugin", engine->newObject());
    */
    SetMethod("require", Require);
    SetMethod("include", Include);
}
