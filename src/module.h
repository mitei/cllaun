#pragma once

#include "v8.h"
#include <QSharedPointer>

namespace cllaun {

/**
 * Default module base.
 */
class Module {
public:

  virtual ~Module() {}

  virtual v8::Handle<v8::Value> NewInstance() = 0;
  v8::Isolate* GetIsolate() { return isolate_; }

protected:
  Module(v8::Isolate* isolate) : isolate_(isolate) {}

private:
  v8::Isolate* isolate_;

private:
  Module() {}
};

typedef QSharedPointer<Module> ModulePtr;

}
