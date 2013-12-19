#include "api_clipboard.h"

#include <QApplication>
#include <QClipboard>

#include "api.h"
#include "core.h"


void cllaun::initClipboard() {
    QClipboard* cb = QApplication::clipboard();
    QScriptValue cb_obj = cllaun::Core::engine()->newQObject(cb);
}

