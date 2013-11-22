#include "api.h"
#include "api_clipboard.h"
#include <QApplication>
#include <QClipboard>

static QScriptValue Get(QScriptContext* context, QScriptEngine* engine) {

}

void cllaun::InitClipboard(QScriptEngine* engine) {
    QClipboard* clipboard = QApplication::clipboard();
}

