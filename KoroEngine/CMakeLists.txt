file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.h")

# Create the library
add_library(KoroEngine SHARED ${SOURCES} ${HEADERS})


# Tells Platform.h to use 'dllexport' (on Windows) or 'default' (on Linux)
target_compile_definitions(KoroEngine PRIVATE KORO_BUILD_DLL)

# Ensures the Sandbox can find Platform.h and Test.h
target_include_directories(KoroEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(KoroEngine PRIVATE spdlog)
