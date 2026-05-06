# KoroEngine – Maintenance and Build Guide

This document describes how to build, modify, and maintain the project.

KoroEngine uses **Premake5** as a meta-build system, with custom Python scripts wrapping generation and build steps. The setup reflects an experimental workflow and may change frequently.

---

## 1. Build Workflow

### Recommended (Scripted)

```bash
python GenerateProject.py && python Build.py
```

### What This Does

### GenerateProject.py

* Bootstraps Wayland protocol files (Linux only)
* Initializes and updates git submodules
* Selects the correct Premake binary for the host OS
* Generates platform-specific build files:

  * Linux → `gmake`
  * Windows → `vs2022`
  * macOS → `xcode`

### Build.py

* Linux:

  * Runs `make -jN config=debug`
  * Uses `bear` (if installed) to generate `compile_commands.json`
* Windows:

  * No automation; build via Visual Studio
* macOS:

  * Not implemented

---

## 2. Manual Build (Fallback)

### Linux

```bash
vendor/bin/premake/premake5 gmake
make config=debug -j$(nproc)
```

### Windows

```bash
vendor/bin/premake/premake5.exe vs2022
```

Open the generated `.sln` file and build using Visual Studio.

---

## 3. Build Configurations

Available configurations:

* `Debug`
* `Release`
* `Dist`

Output format:

```
bin/<Config>-<System>-<Arch>/<ProjectName>
```

Example:

```
bin/Debug-linux-x86_64/Sandbox/Sandbox
```

---

## 4. Runtime Linking

The engine is built as a **shared library** and loaded by the Sandbox application.

### Linux

Uses:

```bash
-Wl,-rpath,'$ORIGIN'
```

Ensures `KoroEngine.so` is resolved relative to the executable.

### macOS

Uses:

```bash
-Wl,-rpath,@loader_path
```

---

## 5. Wayland Bootstrap (Linux)

`GenerateProject.py` includes a bootstrap step:

* Uses `wayland-scanner` to generate protocol headers and source files
* Outputs to:

```
vendor/glfw/src/
```

Current state:

* X11 is active (`_GLFW_X11`)
* Wayland files are generated but not enabled (`_GLFW_WAYLAND` is commented)

---

## 6. Adding Source Files

1. Place files under:

   * `KoroEngine/src/`
   * `Sandbox/src/`

2. Regenerate build files:

```bash
python GenerateProject.py
```

Premake must rescan file lists for changes to take effect.

---

## 7. Adding Dependencies

1. Add submodule:
  
```bash
    git submodule add <url> vendor/<name>
    ```

2. Update `premake5.lua`:
    Include directory:
    ```lua
        includedirs { "vendor/<name>/include" }
    ```

    Link library (if required):

    ```lua
    links { "<name>" }
    ```

3. Regenerate project files.

---

## 8. LSP Integration

### Linux (Neovim / clangd)

Preferred:

```bash
bear -- make config=debug -j$(nproc)
```

Or:

```bash
python Build.py
```

This generates:

``` bash
compile_commands.json
```

### VS Code

Ensure:

```json
"compileCommands": "${workspaceFolder}/compile_commands.json"
```

### Visual Studio

No manual setup required.

---

## 9. Common Issues

### Missing Shared Library

If `KoroEngine.so` is not found:

* Verify post-build copy step executed
* Check output directory structure
* Ensure `rpath` flags are applied correctly

---

### LSP Errors / Missing Includes

Cause: outdated `compile_commands.json`

Fix:

```bash
bear -- make clean
bear -- make config=debug
```

---

### Wayland Errors

If protocol files are missing:

```bash
sudo apt install wayland-protocols
```

Then:

```bash
python GenerateProject.py
```

---

## 10. Current State Notes

* Linux (X11) is the primary development environment
* Wayland support is experimental
* macOS path is incomplete
* Build system is intentionally flexible for experimentation

---

## 11. Maintenance Rule

Whenever files are:

* added
* removed
* renamed

Regenerate build files:

```bash
python GenerateProject.py
```

All other steps (linking, output placement) are handled by the existing build configuration.
