#pragma once

#include "v8.h"

#ifdef _WIN32
# ifdef BUILDING_CLLAUN
#   define CLLAUN_EXTERN __declspec(dllexport)
# else
#   define CLLAUN_EXTERN __declspec(dllimport)
# endif
#else
# define CLLAUN_EXTERN /* nothing */
#endif

namespace cllaun {

typedef void (*PluginRegisterFunc)(
    v8::Isolate* isolate, v8::Handle<v8::ObjectTemplate> templ);
extern "C" CLLAUN_EXTERN
    void RegisterPlugin(const char* name, PluginRegisterFunc f);

}

// define CLLAUN_CTOR
#if defined(_MSC_VER)
#pragma section(".CRT$XCU", read)
#define CLLAUN_CTOR(fn)\
  static void __cdecl fn(void);\
  __declspec(dllexport, allocate(".CRT$XCU"))\
    void (__cdecl*fn ## _)(void) = fn;\
  static void __cdecl fn(void)
#else
#define CLLAUN_CTOR(fn)\
  static void fn(void) __attribute__((constructor));\
  static void fn(void)
#endif
// end CLLAUN_CTOR

#define REGISTER_CLLAUN_PLUGIN(name, func)\
  extern "C" {\
    CLLAUN_CTOR(_register_ ## name) {\
      cllaun::RegisterPlugin(#name, func);\
    }\
  }
// end REGISTER_CLLAUN_PLUGIN

