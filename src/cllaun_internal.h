#pragma once
#include "v8.h"
#include "module/modules.h"

namespace cllaun {

class Internal {
public:
  static Internal* GetInstance();
  static ModulePtr GetModules();
  static v8::Isolate* GetIsolate();

private:
  ModulePtr modules;
  v8::Isolate* isolate_;

private:
  Internal(v8::Isolate* isolate = nullptr);
  Internal(const Internal&);
  Internal& operator=(const Internal&);
};

}
