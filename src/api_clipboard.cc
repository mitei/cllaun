#include <QApplication>
#include <QClipboard>

#include "api.h"
#include "core.h"

#include "api_clipboard.h"

void cllaun::InitClipboard() {
    QClipboard* cb = QApplication::clipboard();
    QScriptValue cb_obj = cllaun::Core::Engine()->newQObject(cb);
}

