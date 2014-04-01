#pragma once
#include "module.h"

namespace cllaun {
namespace module {

class Widgets : public Module {
public:
  static ModulePtr New(v8::Isolate* isolate) {
    return ModulePtr(new Widgets(isolate));
  }
  ~Widgets();

  v8::Handle<v8::Value> NewInstance();

private:
  Widgets(v8::Isolate* isolate) : Module(isolate) {}
  v8::Persistent<v8::ObjectTemplate> persistent_templ;
};

}
}
