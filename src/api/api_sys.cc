#include "api/api_sys.h"
#include "system.h"
#include "dirs.h"
#include <QScriptEngine>
#include <QString>
#include <QFileInfo>


QScriptString cllaun::API_Sys::str_paths;

QScriptValue cllaun::API_Sys::execute(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() == 0)
        return QScriptValue(false);

    QString path = context->argument(0).toString();
    const QStringList args = context->argument(1).isArray() ?
                                 qscriptvalue_cast<QStringList>(context->argument(1)) :
                                 QStringList();
    QFileInfo path_info(path);
    if (!path_info.isAbsolute() && !path_info.isRelative()) {
        const QStringList paths = qscriptvalue_cast<QStringList>(context->callee().property(str_paths));
        const QStringList name_filter = QStringList() << path << path + ".*";
        const QStringList entries = cllaun::Dirs(paths).entryList(name_filter, QDir::Files|QDir::Executable);
        if (!entries.isEmpty())
            path = entries[0];
    }

    return QScriptValue(cllaun::sys_execute(path, args));
}

QScriptValue cllaun::API_Sys::open(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    if (context->argumentCount() == 0)
        return QScriptValue(false);

    const QString path = context->argument(0).toString();
    const QFileInfo path_info(path);
    if (path_info.exists())
        return QScriptValue(cllaun::sys_open(path));
    return QScriptValue(false);
}

QScriptValue cllaun::API_Sys::exit(QScriptContext* context, QScriptEngine* engine) {
    Q_UNUSED(engine)
    cllaun::sys_exit(context->argument(0).toInt32());
    return QScriptValue(QScriptValue::UndefinedValue);
}


cllaun::API_Sys::API_Sys(QScriptEngine* engine) {
    str_paths = engine->toStringHandle("paths");

    QScriptValue sys_obj = engine->newObject();
    QScriptValue execute_obj = engine->newFunction(execute);
    execute_obj.setProperty(str_paths, engine->newArray(), QScriptValue::Undeletable);
    sys_obj.setProperty("execute", execute_obj, QScriptValue::ReadOnly|QScriptValue::Undeletable);
    sys_obj.setProperty("open", engine->newFunction(open), QScriptValue::ReadOnly|QScriptValue::Undeletable);
    sys_obj.setProperty("exit", engine->newFunction(exit), QScriptValue::ReadOnly|QScriptValue::Undeletable);

    engine->globalObject().setProperty("sys", sys_obj, QScriptValue::ReadOnly|QScriptValue::Undeletable);
}
