#include "api/api_file.h"
#include "api/file/file.h"
#include <QFile>
#include <QScriptEngine>


QScriptValue cllaun::API_File::fileConstructor(QScriptContext* context, QScriptEngine* engine, void* proto) {
    QScriptValue instance = engine->newObject();
    instance.setData(engine->newQObject(new QFile, QScriptEngine::AutoOwnership));
    instance.setPrototype(*static_cast<QScriptValue*>(proto));
    return instance;
}

QScriptValue cllaun::API_File::File_rename(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 2) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString old_name = context->argument(0).toString();
    const QString new_name = context->argument(1).toString();
    return QScriptValue(QFile::rename(old_name, new_name));
}

QScriptValue cllaun::API_File::File_copy(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 2) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString src_name = context->argument(0).toString();
    const QString dst_name = context->argument(1).toString();
    return QScriptValue(QFile::copy(src_name, dst_name));
}

QScriptValue cllaun::API_File::File_remove(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 1) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString name = context->argument(0).toString();
    return QScriptValue(QFile::remove(name));
}

QScriptValue cllaun::API_File::File_exists(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 1) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString name = context->argument(0).toString();
    return QScriptValue(QFile::exists(name));
}

QScriptValue cllaun::API_File::File_link(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 2) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString src_name = context->argument(0).toString();
    const QString link_name = context->argument(1).toString();
    return QScriptValue(QFile::rename(src_name, link_name));
}


/*!
 * @brief File 関連 API の初期化
 */
cllaun::API_File::API_File(QScriptEngine* engine) {
    static QScriptValue file_proto = engine->newQObject(new FileProto(engine));
    QScriptValue file_constructor = engine->newFunction(fileConstructor, &file_proto);
    file_constructor.setProperty("rename", engine->newFunction(File_rename), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("copy", engine->newFunction(File_copy), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("remove", engine->newFunction(File_remove), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("exists", engine->newFunction(File_exists), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("link", engine->newFunction(File_link), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    engine->globalObject().setProperty("File", file_constructor, QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
