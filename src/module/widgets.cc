#include "widgets.h"

using namespace v8;

cllaun::module::Widgets::~Widgets()
{
  persistent_templ.Reset();
}

Handle<Value> cllaun::module::Widgets::NewInstance()
{
  Isolate* i = GetIsolate();
  EscapableHandleScope handle_scope(i);
  Handle<ObjectTemplate> templ;

  if (persistent_templ.IsEmpty()) {
    templ = ObjectTemplate::New(i);
    persistent_templ.Reset(i, templ);
  } else {
    templ = Local<ObjectTemplate>::New(i, persistent_templ);
  }
  return handle_scope.Escape<Object>(templ->NewInstance());
}
