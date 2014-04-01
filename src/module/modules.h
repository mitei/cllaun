#pragma once

#include "v8.h"
#include "module.h"
#include <QString>
#include <QHash>

namespace cllaun {
namespace module {

class Modules : public Module {
public:
  static ModulePtr New(v8::Isolate* isolate) {
    return ModulePtr(new Modules(isolate));
  }

  ~Modules();

  void RegisterNativePlugin(const QString& name,
                            v8::Handle<v8::ObjectTemplate>& tmepl);
  void RegisterDefaultModules(const QString& name,
                              ModulePtr module);

  v8::Handle<v8::Value> Require(const QString& name);
  void Include(v8::Handle<v8::Context> context,
               const QString& file_path);

  v8::Handle<v8::Value> NewInstance();
  v8::Handle<v8::ObjectTemplate> Create();
  void Install(v8::Handle<v8::ObjectTemplate>& tmepl);

  v8::Handle<v8::Array> GetPluginPaths();

private:
  Modules(v8::Isolate* isolate);
  typedef v8::CopyablePersistentTraits<v8::ObjectTemplate>::CopyablePersistent
          PersistentPlugin;
  v8::Persistent<v8::Array> modules_require_paths_array;
  v8::Persistent<v8::ObjectTemplate> modules_global_template;
  QHash<QString, PersistentPlugin> native_plugins;
  QHash<QString, ModulePtr> default_modules;
};

}
}
