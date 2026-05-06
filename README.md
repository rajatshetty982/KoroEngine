# KoroEngine

KoroEngine is a "from-scratch" C++ game engine built as a
learning project to understand engine architecture,
rendering pipelines, platform abstraction, and build systems.

The project does not aim to be production-ready.
It is intentionally structured to allow experimentation
with different build systems, platform layers, and architectural decisions.

## Architecture Overview

The repository is split into two primary targets:

- KoroEngine: Shared library (.so/.dll) containing core engine systems
- Sandbox: Client application used to test and drive the engine

Key subsystems currently implemented:

- Core application layer (entry point, logging, platform abstraction)
- Event system with buffered dispatch (Event + EventBuffer)
- Platform-specific compilation paths (Windows/Linux/macOS)
- GLFW-based windowing (with X11 active, Wayland optional,
to be manually switched in the vendor/glfw/premake5.lua)

The engine is built as a shared library and loaded by
the Sandbox at runtime. On Linux and macOS, runtime linking is handled via rpath.

## Build System

KoroEngine uses Premake5 as a meta-build system.
Instead of invoking Premake manually, the project provides a wrapper:

- GenerateProject.py → generates platform-specific build files
- Build.py → executes the build (Linux-focused currently)

## Standard Workflow

``` bash
 python GenerateProject.py
 python Build.py
```

This performs:

1. Wayland protocol bootstrap (Linux only, safe to ignore if using X11,
if using Wayland, you need to manually change the
vendor/glfw/premake5.lua to uncomment the Wayland build)
2. Git submodule initialization
3. Premake execution (gmake / vs2022 / xcode)
4. Build execution (make with parallel jobs on Linux)

## Platform Notes

### Linux (primary environment)

- Uses X11 backend by default (_GLFW_X11)
- Wayland support exists but is not currently enabled in GLFW defines
- Requires OpenGL, X11, and standard system libraries

## Dependencies (Debian/Ubuntu-based)

``` bash
sudo apt install libx11-dev libxcursor-dev libxinerama-dev libxrandr-dev \
                 libxi-dev libwayland-dev wayland-protocols \
                 libxkbcommon-dev libgl1-mesa-dev
```

## Windows

- Generates Visual Studio solution (vs2022)
- Build through Visual Studio (MSBuild)

## macOS

- Premake generates Xcode projects
- Not actively maintained or tested

## Third-Party Dependencies

Managed via git submodules:

- GLFW (windowing/input)
- spdlog (logging)

All dependencies are built from source as part of the project.

## LSP / Tooling

On Linux, Build.py optionally integrates with Bear to generate:
```

compile_commands.json
```

This enables proper IntelliSense for:

- Neovim (clangd)
- VS Code (C/C++ extension)

## Project Structure

``` bash
KoroEngine/
├── KoroEngine/        # Engine source (shared library)
├── Sandbox/           # Client application
├── vendor/            # Third-party dependencies
├── bin/               # Output binaries
├── bin-int/           # Intermediate build files
├── premake5.lua       # Root build configuration
├── GenerateProject.py
├── Build.py
```

## Intent

- Engine architecture decisions
- Cross-platform abstractions
- Build systems (Premake, Make, MSBuild, etc.)
- Low-level systems design

Expect frequent changes, inconsistencies, and rewrites as understanding improves.
