#include "cllaun.h"
#include "cllaun_internal.h"
#include <QString>

using namespace v8;

//extern "C" CLLAUN_EXTERN void cllaun::RegisterPlugin(
//    const char* name, cllaun::PluginRegisterFunc register_func)
//{
//  Isolate* isolate = Isolate::GetCurrent();
//  Handle<ObjectTemplate> templ = ObjectTemplate::New(isolate);
//  register_func(isolate, templ);
//  const QString plugin_name = QString::fromUtf8(name);
//  PluginManager::GetManager()->RegisterNativePlugin(plugin_name, templ);
//}

extern "C" CLLAUN_EXTERN void cllaun::RegisterPlugin(
    const char* name, cllaun::PluginRegisterFunc register_func)
{
  Isolate* isolate = Internal::GetIsolate();
  Handle<ObjectTemplate> templ = ObjectTemplate::New(isolate);
  register_func(isolate, templ);
  module::Modules* modules =
      dynamic_cast<module::Modules*>(Internal::GetModules().data());
  modules->RegisterNativePlugin(QString(name), templ);
}
