#include "console.h"
#include <QDebug>

using namespace v8;

namespace {

void console_log(const FunctionCallbackInfo<Value>& info)
{
  qDebug() << "log";
  // TODO
}

void console_dir(const FunctionCallbackInfo<Value>& info)
{
  qDebug() << "dir";
  // TODO
}

}

cllaun::module::Console::~Console()
{
  persistent_templ.Reset();
}

Handle<Value> cllaun::module::Console::NewInstance()
{
  Isolate* i = GetIsolate();
  EscapableHandleScope handle_scope(i);
  Handle<ObjectTemplate> templ;
  if(persistent_templ.IsEmpty()) {
    templ = ObjectTemplate::New(i);
    templ->Set(String::NewFromUtf8(i, "log"),
               FunctionTemplate::New(i, console_log),
               static_cast<PropertyAttribute>(DontDelete|ReadOnly));
    templ->Set(String::NewFromUtf8(i, "dir"),
               FunctionTemplate::New(i, console_dir),
               static_cast<PropertyAttribute>(DontDelete|ReadOnly));
    persistent_templ.Reset(i, templ);
  } else {
    templ = Local<ObjectTemplate>::New(i, persistent_templ);
  }
  return handle_scope.Escape<Object>(templ->NewInstance());
}
