#include <QApplication>
#include <v8.h>
#include <QDebug>
#include "cllaun_internal.h"

#include "module/system.h"
#include "module/modules.h"
#include "module/console.h"

using namespace v8;

void print(const FunctionCallbackInfo<Value>& info)
{
  qDebug() << *String::Utf8Value(info[0]);
}

int main(int argc, char** argv)
{
  using cllaun::module::Modules;

  QApplication app(argc, argv);

  Isolate* isolate = cllaun::Internal::GetIsolate();
  HandleScope handle_scope(isolate);
  cllaun::module::Modules* modules =
      dynamic_cast<cllaun::module::Modules*>(
        cllaun::Internal::GetModules().data());
  modules->RegisterDefaultModules("system",
                                  cllaun::module::System::New(isolate));
  modules->RegisterDefaultModules("console",
                                  cllaun::module::Console::New(isolate));
  modules->RegisterDefaultModules("modules", cllaun::Internal::GetModules());

  Handle<ObjectTemplate> global_templ = modules->Create();
  global_templ->Set(String::NewFromUtf8(isolate, "print"),
                    FunctionTemplate::New(isolate, print));
  Handle<Context> context = Context::New(isolate, nullptr, global_templ);
  Context::Scope context_scope(context);
  Handle<Object> global_proto = context->Global()->GetPrototype()->ToObject();
  global_proto->Set(String::NewFromUtf8(isolate, "global"), global_proto,
                    static_cast<PropertyAttribute>(DontDelete|ReadOnly));
  Handle<Function> require_func =
      global_proto->Get(String::NewFromUtf8(isolate, "require")).As<Function>();
  require_func->Set(String::NewFromUtf8(isolate, "paths"),
                    modules->GetPluginPaths());

  modules->Include(context, ".cllaun");

  return 0;
  //return app.exec();
}
