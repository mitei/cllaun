#include "api_file.h"

#include <QFile>

#include "api.h"
#include "core.h"


#define c_engine cllaun::Core::Engine()

Q_SCRIPT_DECLARE_QMETAOBJECT(QFile, QObject*)

/*!
 * @brief File 関連 API の初期化
 */
void cllaun::InitFile() {
    QScriptValue file_class = c_engine->scriptValueFromQMetaObject<QFile>();
    /*
    QScriptValue file_class = c_engine->newFunction(New);
    QScriptValue proto = c_engine->newObject();
    proto.setProperty("exists", c_engine->newFunction(Exists));
    file_class.setProperty("prototype", proto);
    */
    c_engine->globalObject().setProperty("File", file_class);
}

#undef c_engine
