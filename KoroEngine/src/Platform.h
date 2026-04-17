#pragma once

// Strategy: Platform Detection & 64-bit Check
#ifdef _WIN32
    #ifndef _WIN64
        #error "KoroEngine only supports 64-bit Windows!"
    #endif
    #ifdef KORO_BUILD_DLL
        #define KORO_API __declspec(dllexport)
    #else
        #define KORO_API __declspec(dllimport)
    #endif
#elif defined(__linux__)
    #define KORO_API __attribute__((visibility("default")))
#else
    #error "KoroEngine only supports Windows and Linux for now!"
#endif
