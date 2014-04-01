#include "modules.h"
#include "cllaun_internal.h"
#include "dirs.h"
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QLibrary>

using namespace v8;

namespace {

void require(const FunctionCallbackInfo<Value>& info)
{
  HandleScope handle_scope(info.GetIsolate());
  if (info.Length() < 1) {
    info.GetIsolate()->ThrowException(Exception::Error(
        String::NewFromUtf8(info.GetIsolate(),
                            "Argument Error: Given arguments is too few.")));
    return;
  }
  Handle<Value> module_id = info[0];
  cllaun::module::Modules* modules =
      dynamic_cast<cllaun::module::Modules*>(
        cllaun::Internal::GetModules().data());
  info.GetReturnValue().Set(modules->Require(*String::Utf8Value(module_id)));
}

void include(const FunctionCallbackInfo<Value>& info)
{
  HandleScope handle_scope(info.GetIsolate());
  if (info.Length() < 1) {
    info.GetIsolate()->ThrowException(Exception::Error(
        String::NewFromUtf8(info.GetIsolate(),
                            "Argument Error: Given arguments is too few.")));
    return;
  }
  Handle<Value> file_path = info[0];
  Handle<Context> context = info.GetIsolate()->GetCurrentContext();
  cllaun::module::Modules* modules =
      dynamic_cast<cllaun::module::Modules*>(
        cllaun::Internal::GetModules().data());
  modules->Include(context, *String::Utf8Value(file_path));
}

} // namespace end


cllaun::module::Modules::Modules(v8::Isolate* isolate)
    : Module(isolate)
{
}

cllaun::module::Modules::~Modules()
{
  modules_require_paths_array.Reset();
  modules_global_template.Reset();
  foreach (PersistentPlugin t, native_plugins) {
    t.Reset();
  }
}

void cllaun::module::Modules::RegisterNativePlugin(
    const QString& name,
    Handle<ObjectTemplate>& templ)
{
  native_plugins.insert(name, PersistentPlugin(GetIsolate(), templ));
}

void cllaun::module::Modules::RegisterDefaultModules(
    const QString& name,
    ModulePtr module)
{
  default_modules.insert(name, module);
}

Handle<Value> cllaun::module::Modules::Require(
    const QString& name)
{
  qDebug() << "Require";
  EscapableHandleScope handle_scope(GetIsolate());
  Handle<Value> result_module;

  if (default_modules.contains(name)) {
    // search default module
    return handle_scope.Escape<Value>(
        default_modules.value(name)->NewInstance());
  }

  // search plugin
  Handle<Array> plugin_paths = GetPluginPaths();
  const QString plugin_init_script_name("__init__.js");
  for (uint32_t i = 0; i < plugin_paths->Length(); ++i) {
    QDir plugin_dir(QString(*String::Utf8Value(plugin_paths->Get(i))));
    plugin_dir.cd(name);
    if (!plugin_dir.exists()) continue;
    if (plugin_dir.exists(plugin_init_script_name)) {
      // if "__init__.js" is exists
      const QString plugin_init_script_file_path =
          plugin_dir.absoluteFilePath(plugin_init_script_name);

      // run native plugin.
      const QString native_plugin_name = name + ".cllaun";
      Handle<Object> plugin_native_obj;
      if (plugin_dir.exists(native_plugin_name)) {
        if (!native_plugins.contains(name)) {
          QLibrary native_plugin_lib(
              plugin_dir.absoluteFilePath(native_plugin_name));
          native_plugin_lib.load();
        }
        Handle<ObjectTemplate> plugin_templ =
            Local<ObjectTemplate>::New(GetIsolate(), native_plugins.value(name));
        plugin_native_obj = plugin_templ->NewInstance();
      } else {
        plugin_native_obj = Object::New(GetIsolate());
      }

      Handle<ObjectTemplate> global_templ =
          Local<ObjectTemplate>::New(GetIsolate(), modules_global_template);
      Handle<Context> context =
          Context::New(GetIsolate(), 0, global_templ);
      Handle<Object> global = context->Global()->GetPrototype()->ToObject();
      global->Set(String::NewFromUtf8(GetIsolate(), "__native__"),
                  plugin_native_obj);
      Handle<Value> exports_key = String::NewFromUtf8(GetIsolate(), "__exports__");
      global->Set(String::NewFromUtf8(GetIsolate(), "__exports__"), Object::New(GetIsolate()));
      // run "__init__.js".
      Include(context, plugin_init_script_file_path);
      result_module = global->Get(exports_key);
      break;
    } else {
      // if "__init__.js" is not exists
      continue;
    }
  }

  if (result_module.IsEmpty()) {
    result_module = Undefined(GetIsolate());
  }
  return handle_scope.Escape<Value>(result_module);
}

void cllaun::module::Modules::Include (
    Handle<v8::Context> context,
    const QString& file_path)
{
  qDebug() << "Include";
  HandleScope handle_scope(GetIsolate());
  Context::Scope context_scope(context);

  QFile file(file_path);
  if (file.exists()) {
    file.open(QFile::ReadOnly);
    Handle<String> script_str = String::NewFromUtf8(
        context->GetIsolate(),
        QString::fromUtf8(file.readAll()).toStdString().c_str());
    Handle<String> script_file_name =
        String::NewFromUtf8(GetIsolate(), file_path.toStdString().c_str());
    Handle<Script> script = Script::Compile(script_str, script_file_name);
    script->Run();
  }
}

Handle<Value> cllaun::module::Modules::NewInstance()
{
  return Create()->NewInstance();
}

Handle<ObjectTemplate> cllaun::module::Modules::Create()
{
  Handle<ObjectTemplate> templ;
  if (modules_global_template.IsEmpty()) {
    templ = ObjectTemplate::New(GetIsolate());
    modules_global_template.Reset(GetIsolate(), templ);
    Install(templ);
  } else {
    templ = Local<ObjectTemplate>::New(GetIsolate(), modules_global_template);
  }
  return templ;
}

void cllaun::module::Modules::Install(Handle<ObjectTemplate>& templ)
{
    templ->Set(String::NewFromUtf8(GetIsolate(), "require"),
               FunctionTemplate::New(GetIsolate(), require),
               static_cast<PropertyAttribute>(DontDelete|ReadOnly));
    templ->Set(String::NewFromUtf8(GetIsolate(), "include"),
               FunctionTemplate::New(GetIsolate(), include),
               static_cast<PropertyAttribute>(DontDelete|ReadOnly));
}

Handle<Array> cllaun::module::Modules::GetPluginPaths()
{
  EscapableHandleScope handle_scope(GetIsolate());
  Handle<Array> plugin_paths;
  if (modules_require_paths_array.IsEmpty()) {
    plugin_paths = Array::New(GetIsolate());
    modules_require_paths_array.Reset(GetIsolate(), plugin_paths);
  } else {
    plugin_paths = Local<Array>::New(GetIsolate(), modules_require_paths_array);
  }
  return handle_scope.Escape<Array>(plugin_paths);
}
