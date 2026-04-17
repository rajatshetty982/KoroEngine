cmake_minimum_required(VERSION 3.10)
project(KoroEngine)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()


# --- 64-bit Enforcement ---
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "KoroEngine does not support 32-bit systems. Please use a 64-bit architecture.")
endif()

if(WIN32)
    set(KORO_PLATFORM "Windows")
else()
    set(KORO_PLATFORM "Linux")
endif()

# for execuatables to find the libs
# TODO: when adding 3rd-party DLLs, we may need a 'POST_BUILD' command 
# to copy them into the output folder.
if(UNIX)
    if(APPLE)
        # macOS: Search for .dylib files in the same directory as the executable
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'@loader_path'")
    else()
        # Linux: Search for .so files in the same directory as the executable ($ORIGIN)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'")
        set(CMAKE_BUILD_RPATH "$ORIGIN")
    endif()
# elseif(WIN32)
    # Windows: DLLs are automatically searched in the same directory as the .exe.
endif()

# Output directories: bin/Debug-Linux-x86_64/
set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/bin/${CMAKE_BUILD_TYPE}-${KORO_PLATFORM}-${CMAKE_SYSTEM_PROCESSOR}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

add_subdirectory(libs/spdlog)

add_subdirectory(KoroEngine)
add_subdirectory(Sandbox)
