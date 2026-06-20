# just a dumb build script for me, because I don't want to remember what I used for this project(I am experimenting heavily on every other build system, still in my early learning phase)

import multiprocessing
import platform
import shutil
import subprocess
import sys


def get_cpu_count():
    return multiprocessing.cpu_count()


def build():
    host_os = platform.system()
    config = "debug"

    if host_os == "Linux":
        has_bear = shutil.which("bear") is not None

        make_cmd = [
            "make",
            f"-j{get_cpu_count()}",
            f"config={config}",
            # f"verbose=1"
        ]

        cmd = make_cmd

        if has_bear:
            cmd = [
                "bear",
                "--append",
                "--output",
                "compile_commands.json",
                "--"
            ] + make_cmd

        print(f"Executing: {' '.join(cmd)}")

        try:
            subprocess.run(cmd, check=True)

        except subprocess.CalledProcessError as e:
            print(f"\n[!] BUILD FAILED: exited with code {e.returncode}")
            sys.exit(e.returncode)

        print("\n[+] Build Successful.")

    elif host_os == "Windows":
        print("Use MSBuild or open the generated Visual Studio solution.")

    elif host_os == "Darwin":
        print("No macOS build path yet.")

    else:
        print(f"Unsupported platform: {host_os}")
        sys.exit(1)


if __name__ == "__main__":
    build()
