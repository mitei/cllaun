#include "api/api_file.h"
#include "api/file/file.h"
#include "api/file/dir.h"
#include <QFile>
#include <QDir>
#include <QScriptEngine>

Q_DECLARE_METATYPE(QDir)
Q_DECLARE_METATYPE(QDir::Filters)
Q_DECLARE_METATYPE(QDir::SortFlags)


QScriptValue cllaun::API_File::fileConstructor(QScriptContext* context, QScriptEngine* engine, void* proto) {
    QScriptValue instance = context->isCalledAsConstructor() ?
                                context->thisObject() :
                                engine->newObject();
    QScriptValue arg0 = context->argument(0);
    QFile* data = arg0.isString() ? new QFile(arg0.toString()) : new QFile;
    instance.setData(engine->newQObject(data, QScriptEngine::AutoOwnership));
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


QScriptValue cllaun::API_File::dirConstructor(QScriptContext* context, QScriptEngine* engine, void* proto) {
    QScriptValue arg0 = context->argument(0);
    Dir* data = arg0.isString() ? new Dir(arg0.toString()) : new Dir();
    QScriptValue instance = engine->newQObject(data, QScriptEngine::ScriptOwnership);
    instance.setPrototype(*static_cast<QScriptValue*>(proto));
    return instance;
}

QScriptValue cllaun::API_File::Dir_current(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    Q_UNUSED(context)
    return QScriptValue(QDir::currentPath());
}

QScriptValue cllaun::API_File::Dir_home(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    Q_UNUSED(context)
    return QScriptValue(QDir::homePath());
}

QScriptValue cllaun::API_File::Dir_temp(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    Q_UNUSED(context)
    return QScriptValue(QDir::tempPath());
}

QScriptValue cllaun::API_File::Dir_setCurrent(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 1) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString path = context->argument(0).toString();
    return QScriptValue(QDir::setCurrent(path));
}

QScriptValue cllaun::API_File::Dir_toNativeSeparators(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() < 1) {
        // TODO: error message
        context->throwError(QScriptContext::TypeError, "Argument Error: ");
    }
    const QString path = context->argument(0).toString();
    return QScriptValue(QDir::toNativeSeparators(path));
}

QScriptValue cllaun::API_File::filtersToScriptValue(QScriptEngine* engine, const QDir::Filters& f) {
    return QScriptValue(static_cast<int>(f));
}

void cllaun::API_File::filtersFromScriptValue(const QScriptValue& obj, QDir::Filters& f) {
    f = QDir::Filters(obj.toInt32());
}

QScriptValue cllaun::API_File::sortToScriptValue(QScriptEngine* engine, const QDir::SortFlags& s) {
    return QScriptValue(static_cast<int>(s));
}

void cllaun::API_File::sortFromScriptValue(const QScriptValue& obj, QDir::SortFlags& s) {
    s = QDir::SortFlags(obj.toInt32());
}


/*!
 * @brief File 関連 API の初期化
 */
cllaun::API_File::API_File(QScriptEngine* engine) {
    qScriptRegisterMetaType(engine, filtersToScriptValue, filtersFromScriptValue);
    qScriptRegisterMetaType(engine, sortToScriptValue, sortFromScriptValue);
    static QScriptValue file_proto = engine->newQObject(new FileProto(engine));
    QScriptValue file_constructor = engine->newFunction(fileConstructor, &file_proto);
    file_constructor.setProperty("rename", engine->newFunction(File_rename), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("copy", engine->newFunction(File_copy), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("remove", engine->newFunction(File_remove), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("exists", engine->newFunction(File_exists), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    file_constructor.setProperty("link", engine->newFunction(File_link), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    static QScriptValue dir_proto = engine->newQObject(new DirProto(engine));
    QScriptValue dir_constructor = engine->newFunction(dirConstructor, &dir_proto);
    dir_constructor.setProperty("current", engine->newFunction(Dir_current), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("home", engine->newFunction(Dir_home), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("temp", engine->newFunction(Dir_temp), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("setCurrent", engine->newFunction(Dir_setCurrent), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("toNativeSeparator", engine->newFunction(Dir_toNativeSeparators), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    dir_constructor.setProperty("Dirs", QScriptValue(static_cast<int>(QDir::Dirs)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("AllDirs", QScriptValue(static_cast<int>(QDir::AllDirs)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Files", QScriptValue(static_cast<int>(QDir::Files)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Drives", QScriptValue(static_cast<int>(QDir::Drives)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("NoSymLinks", QScriptValue(static_cast<int>(QDir::NoSymLinks)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("NoDotAndDotDot", QScriptValue(static_cast<int>(QDir::NoDotAndDotDot)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("NoDot", QScriptValue(static_cast<int>(QDir::NoDot)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("NoDotDot", QScriptValue(static_cast<int>(QDir::NoDotDot)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("AllEntries", QScriptValue(static_cast<int>(QDir::AllEntries)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Readable", QScriptValue(static_cast<int>(QDir::Readable)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Writable", QScriptValue(static_cast<int>(QDir::Writable)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Executable", QScriptValue(static_cast<int>(QDir::Executable)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Modified", QScriptValue(static_cast<int>(QDir::Modified)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Hidden", QScriptValue(static_cast<int>(QDir::Hidden)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("System", QScriptValue(static_cast<int>(QDir::System)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("CaseSensitive", QScriptValue(static_cast<int>(QDir::CaseSensitive)), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    dir_constructor.setProperty("Name", QScriptValue(static_cast<int>(QDir::Name)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Time", QScriptValue(static_cast<int>(QDir::Time)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Size", QScriptValue(static_cast<int>(QDir::Size)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Type", QScriptValue(static_cast<int>(QDir::Type)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Unsorted", QScriptValue(static_cast<int>(QDir::Unsorted)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("NoSort", QScriptValue(static_cast<int>(QDir::NoSort)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("DirsFirst", QScriptValue(static_cast<int>(QDir::DirsFirst)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("DirsLast", QScriptValue(static_cast<int>(QDir::DirsLast)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("Reversed", QScriptValue(static_cast<int>(QDir::Reversed)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("IgnoreCase", QScriptValue(static_cast<int>(QDir::IgnoreCase)), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    dir_constructor.setProperty("LocaleAware", QScriptValue(static_cast<int>(QDir::LocaleAware)), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    engine->globalObject().setProperty("File", file_constructor, QScriptValue::ReadOnly|QScriptValue::Undeletable);
    engine->globalObject().setProperty("Dir", dir_constructor, QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
