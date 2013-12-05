#include <QFile>

#include "api.h"
#include "core.h"

#include "api_file.h"

#define c_engine cllaun::Core::Engine()

/*!
 * @brief ファイルの存在チェック
 *
 * @return 存在すれば true, 存在しなければ false
 */
static QScriptValue Exists(QScriptContext* context, QScriptEngine* engine) {
    QFile* file = cllaun::GetThis<QFile>(context);

    return file->exists() ? QScriptValue(true) : QScriptValue(false);
}

/*!
 * @brief File コンストラクタ
 *
 * @return 生成した File オブジェクト
 */
static QScriptValue New(QScriptContext* context, QScriptEngine* engine) {
    QFile* file = context->argumentCount() >= 1 && context->argument(0).isString() ?
                new QFile(context->argument(0).toString()) :
                new QFile();
    QScriptValue file_obj = context->isCalledAsConstructor() ?
                engine->newQObject(context->thisObject(), file, QScriptEngine::AutoOwnership) :
                engine->newQObject(file, QScriptEngine::AutoOwnership);

    file_obj.setProperty("exists", engine->newFunction(Exists));
    return file_obj;
}

/*!
 * @brief File 関連 API の初期化
 */
void cllaun::InitFile() {
    QScriptValue file_class = c_engine->newFunction(New);
    QScriptValue proto = c_engine->newObject();
    proto.setProperty("exists", c_engine->newFunction(Exists));
    file_class.setProperty("prototype", proto);
    c_engine->globalObject().setProperty("File", file_class);
}

#undef c_engine
