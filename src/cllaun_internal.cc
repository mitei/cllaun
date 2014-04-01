#include "cllaun_internal.h"


cllaun::Internal::Internal(v8::Isolate* isolate)
    : isolate_(isolate), modules(module::Modules::New(isolate))
{
}

cllaun::Internal* cllaun::Internal::GetInstance()
{
  static Internal instance(v8::Isolate::GetCurrent());
  return &instance;
}

cllaun::ModulePtr cllaun::Internal::GetModules()
{
  return GetInstance()->modules;
}

v8::Isolate* cllaun::Internal::GetIsolate()
{
  return GetInstance()->isolate_;
}
