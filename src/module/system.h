#pragma once
#include "module.h"

namespace cllaun {
namespace module {

class System : public Module {
public:
  static ModulePtr New(v8::Isolate* isolate) {
    return ModulePtr(new System(isolate));
  }
  ~System();

  v8::Handle<v8::Value> NewInstance();

private:
  System(v8::Isolate* isolate) : Module(isolate) {}
  v8::Persistent<v8::ObjectTemplate> persistent_templ;
};

}
}
