#pragma once

// Platform Detection and API Export/Import
#ifdef KORO_PLATFORM_WINDOWS
    #ifdef KORO_BUILD_DLL
        #define KORO_API __declspec(dllexport)
    #else
        #define KORO_API __declspec(dllimport)
    #endif
#elif defined(KORO_PLATFORM_LINUX)
    #define KORO_API __attribute__((visibility("default")))
#else
    #error "KoroEngine only supports Windows and Linux!"
#endif

// Debug Break Logic
#if defined(KORO_PLATFORM_WINDOWS)
    #define KORO_DEBUGBREAK() __debugbreak()
#elif defined(KORO_PLATFORM_LINUX)
    #include <signal.h>
    #define KORO_DEBUGBREAK() raise(SIGTRAP)
#else
    #define KORO_DEBUGBREAK()
#endif

// Assertions
#ifdef KORO_ASSERTS_ENABLED
    #define KORO_ENG_ASSERT(x, ...) do { if(!(x)) { KORO_ENG_ERROR("Assertion failed: {0}", __VA__ARGS__); KORO_DEBUGBREAK(); } } while(0)
    #define KORO_ASSERT(x, ...)     do { if(!(x)) { KORO_ERROR("Assertion failed: {0}", __VA__ARGS__); KORO_DEBUGBREAK(); } } while(0)
#else
    #define KORO_ENG_ASSERT(x, ...)
    #define KORO_ASSERT(x, ...)
#endif
