#pragma once

// Use the defines we set in premake5.lua
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
