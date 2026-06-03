import os
import platform
import subprocess
import sys

def run_command(command, cwd=None):
    """Executes a system command and returns success status."""
    try:
        print("run_command: Running this command: " + command);
        subprocess.check_call(command, shell=True, cwd=cwd)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Command failed with error: {e}")
        return False

def get_premake_path():
    """Identifies the correct Premake binary based on the host OS."""
    system = platform.system()
    base_path = "vendor/bin/premake"

    if system == "Windows":
        return os.path.abspath(os.path.join(base_path, "premake5.exe"))
    elif system == "Darwin": # macOS
        return os.path.abspath(os.path.join(base_path, "mac/premake5"))
    elif system == "Linux":
        return os.path.abspath(os.path.join(base_path, "premake5"))
    else:
        print(f"Unsupported OS: {system}")
        sys.exit(1)

def bootstrap_wayland():
    import platform, os, subprocess
    if platform.system() != "Linux":
        return

    # Dictionary of (Protocol XML Path : Base Output Name)
    protocols = {
        "/usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml": "xdg-shell",
        "/usr/share/wayland-protocols/unstable/xdg-decoration/xdg-decoration-unstable-v1.xml": "xdg-decoration-unstable-v1"
    }

    out_dir = "vendor/glfw/src"
    
    print("--- Protocol Bootstrap ---")
    for xml, name in protocols.items():
        if os.path.exists(xml):
            print(f"Generating: {name}")
            # Generate Header
            subprocess.call(f"wayland-scanner client-header {xml} {out_dir}/{name}-client-protocol.h", shell=True)
            # Generate Private Code
            subprocess.call(f"wayland-scanner private-code {xml} {out_dir}/{name}-protocol.c", shell=True)
        else:
            print(f"[!] Critical: {xml} not found! Check wayland-protocols installation.")

# Ensure this runs BEFORE premake5 in main()

def main():
    bootstrap_wayland();

    # Ensure the repo is ready
    print("Updating submodules...")
    run_command("git submodule update --init --recursive")

    # Locate Premake
    premake_path = get_premake_path()
    if not os.path.exists(premake_path):
        print(f"Critical Error: Premake binary not found at {premake_path}")
        sys.exit(1)

    # Choose the build system action
    system = platform.system()
    if system == "Windows":
        action = "vs2022"
    elif system == "Darwin":
        action = "xcode4"
    elif system == "Linux":
        action = "gmake"
    else:
        print("Not a supported OS")
        print("Aborting!")
        return

    print(f"Generating {action} files using {premake_path}")

    # Generate projects
    if run_command(f"{premake_path} {action}"):
        print("\nSuccess: Build files generated.")

        # Linux-specific: Automatically run Bear if desired
        if system == "Linux":
            print("\n\nNote: If you're using nvim and not using build.py, run a command equivalent of 'bear -- make' to update/create LSP database (compile_commands.json)")
    else:
        print("\nError: Project generation failed.")
        sys.exit(1)

if __name__ == "__main__":
    main()
