#include "api.h"
#include "api_clipboard.h"
#include <QApplication>
#include <QClipboard>

static QScriptValue Get(QScriptContext* context, QScriptEngine* engine) {
}

void cllaun::InitClipboard() {
    QClipboard* cb = QApplication::clipboard();
    QScriptValue cb_obj = cllaun::Core::Engine()->newQObject(cb);
}

