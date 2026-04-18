# KoroEngine Maintenance and Build Guide

This project utilizes Premake5 as a meta-build system. Build configurations and project structures are managed via premake5.lua; do not edit Makefiles or Project files directly.

---

## 1. Building for Different Platforms

### Linux
The primary build tool is GNU Make.
1. Generate Makefiles: premake5 gmake
2. Build: make config=debug -j$(nproc)
   - Available configurations: debug, release, dist.
3. Clean: make clean

### Windows (Visual Studio)
1. Generate Solution: premake5 vs2022 (or vs2019)
2. Build: Open the generated .sln file and execute Build Solution (Ctrl+Shift+B).
3. Note: The post-build script automatically transfers the KoroEngine.dll to the Sandbox directory.

---

## 2. IDE and LSP Integration

### Neovim (LSP / Clangd)
Premake does not natively generate a compilation database. Use Bear (Build EAR) to create the necessary JSON file for your LSP.
1. Generate and Intercept:
   premake5 gmake
   bear -- make config=debug -j$(nproc)
2. Result: A compile_commands.json file is generated in the root directory. Neovim's LSP will now resolve all engine headers and external libraries.

### VS Code
1. Requirements: C/C++ Extension Pack.
2. Configuration: VS Code utilizes the compile_commands.json database.
3. Point to Database: In .vscode/c_cpp_properties.json, ensure the following is set:
   "compileCommands": "${workspaceFolder}/compile_commands.json"

### Visual Studio (Windows)
No manual database setup is required. Premake generates .vcxproj and .filters files that handle IntelliSense and virtual folder organization natively.

---

## 3. Project Modification Procedures

### Adding a New Source File (.cpp / .h)
1. File Placement: Save the file in KoroEngine/src/ or Sandbox/src/.
2. Naming Convention: Use PascalCase (e.g., RendererAPI.cpp).
3. System Refresh: You must regenerate the build files for the new files to be included in the compilation:
   - Linux: premake5 gmake
   - Windows: premake5 vs2022

### Adding an External Library (Submodule)
1. Git Command: git submodule add <url> libs/<name>
2. Update premake5.lua:
   - Add the include path to the includedirs block:
     includedirs { "libs/<name>/include" }
   - If the library requires linking, add the target name to the links block:
     links { "<name>" }

### Adding a New Subfolder
The current Premake script uses recursive wildcards (**.cpp), so files within new subdirectories (e.g., KoroEngine/src/Renderer/) are discovered automatically.
1. Action: Simply run the generation command (premake5 gmake or vs2022) to update the directory mapping in the build files.

---

## 4. Automated Workflow (Neovim Specific)

The <leader>rm keymap in your init.lua is configured as follows:
- Command: clear; make config=debug -j$(nproc) && ./bin/Debug-linux-x86_64/Sandbox/Sandbox
- Logic: It clears the terminal, performs an incremental build using all available CPU cores, and executes the Sandbox binary upon a successful build.

---

## 5. Troubleshooting and Maintenance
- Shared Library Error: If the .so or .dll is not found at runtime, verify that the postbuildcommands in premake5.lua executed correctly.
- LSP Resolution Issues: If Neovim reports false errors, the compile_commands.json is likely outdated. Execute:
  bear -- make clean && bear -- make config=debug
- Architecture: Ensure the environment is x64. KoroEngine does not support 32-bit architectures.

---

### Procedural Summary
Whenever a file is added, deleted, or renamed, execute the premake5 [action] command. All other linking and binary management is automated.
