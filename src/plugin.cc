#include "plugin.h"
#include <QScriptEngine>


cllaun::Plugin::Plugin(QObject* parent)
    : QObject(parent)
{

}

QScriptValue cllaun::Plugin::newQObject(QScriptEngine* engine) {
    Plugin* plugin = new Plugin(engine);
    QScriptValue plugin_obj = engine->newQObject(plugin, QScriptEngine::AutoOwnership);
    plugin_obj.setProperty("ignore", engine->newArray(), QScriptValue::Undeletable);
    return plugin_obj;
}

QStringList cllaun::Plugin::imported() const {
    return engine()->importedExtensions();
}

QStringList cllaun::Plugin::available() const {
    return engine()->availableExtensions();
}

void cllaun::Plugin::import(const QString& name) const {
    QScriptValue result = engine()->importExtension(name);
    // if result is not undefined-value, result is error-object.
    if (!result.isUndefined()) {
        // TODO: Error
        //context()->throwError(QScriptContext::TypeError, result.toString());
    }
}

void cllaun::Plugin::importAll() const {
    QStringList ignore_list = qscriptvalue_cast<QStringList>(thisObject().property("ignore"));
    QStringList available_list = engine()->availableExtensions();
    foreach (const QString name, available_list) {
        if (!ignore_list.contains(name))
            engine()->importExtension(name);
    }
}
