#include "system.h"

#if defined(Q_OS_WIN32)
# define PLATFORM "win"
#elif defined(Q_OS_MACX)
# define PLATFORM "macx"
#elif defined(Q_OS_UNIX)
# define PLATFORM "unix"
#endif

using namespace v8;

cllaun::module::System::~System()
{
  persistent_templ.Reset();
}

Handle<Value> cllaun::module::System::NewInstance()
{
  Isolate* i = GetIsolate();
  EscapableHandleScope handle_scope(i);
  Handle<ObjectTemplate> templ;
  if (persistent_templ.IsEmpty()) {
    templ = ObjectTemplate::New(i);
    templ->Set(String::NewFromUtf8(i, "platform"),
               String::NewFromUtf8(i, PLATFORM),
               static_cast<PropertyAttribute>(ReadOnly|DontDelete));
  } else {
    templ = Local<ObjectTemplate>::New(i, persistent_templ);
  }

  return handle_scope.Escape<Object>(templ->NewInstance());
}

#undef PLATFORM
