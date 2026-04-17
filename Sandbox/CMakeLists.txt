file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(Sandbox ${SOURCES})

# Links to the library created in the other folder
target_link_libraries(Sandbox KoroEngine)
