#pragma once

// ------------------ helpers --------------
#if defined(KORO_DEBUG)
    #define KORO_BUILD_CONFIG "debug"
	#define KORO_ASSERTS_ENABLED
#elif defined(KORO_RELEASE)
    #define KORO_BUILD_CONFIG "release"
#elif defined(KORO_DIST)
    #define KORO_BUILD_CONFIG "dist"
#else
    #define KORO_BUILD_CONFIG "Unknown"
#endif
// --------------- helpers end --------------

// Platform Detection and API Export/Import
#ifdef KORO_PLATFORM_WINDOWS
    #ifdef KORO_BUILD_DLL
        #define KORO_API __declspec(dllexport)
    #else
        #define KORO_API __declspec(dllimport)
    #endif
#elif defined(KORO_PLATFORM_LINUX)
    #define KORO_API __attribute__((visibility("default")))
#elif defined(KORO_PLATFORM_MACOS)
    #define KORO_API __attribute__((visibility("default")))
#else
    #error "Unsupported platform!"
#endif

// Debug Break Logic

#if defined(KORO_PLATFORM_WINDOWS)
    #define KORO_DEBUGBREAK() __debugbreak()
#elif defined(KORO_PLATFORM_LINUX) || defined(KORO_PLATFORM_MACOS)
    #if defined(__GNUC__) || defined(__clang__)
        #define KORO_DEBUGBREAK() __builtin_trap()
    #else
        #include <signal.h>
        #define KORO_DEBUGBREAK() raise(SIGTRAP)
    #endif
#else
    #define KORO_DEBUGBREAK()
#endif

// Assertions
#ifdef KORO_ASSERTS_ENABLED
    #define KORO_ENG_ASSERT(x, ...) do { if(!(x)) { KORO_ENG_ERROR("Assertion failed: {0}", __VA_ARGS__); KORO_DEBUGBREAK(); } } while(0)
    #define KORO_ASSERT(x, ...)     do { if(!(x)) { KORO_ERROR("Assertion failed: {0}", __VA_ARGS__); KORO_DEBUGBREAK(); } } while(0)
#else
    #define KORO_ENG_ASSERT(x, ...)
    #define KORO_ASSERT(x, ...)
#endif


