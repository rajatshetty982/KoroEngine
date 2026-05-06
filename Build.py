# just a dumb build script for me, because I don't want to remember what I used for this project(I am experimenting heavily on every other build system, still in my early learning phase)

import platform
import sys
import subprocess
import multiprocessing

def get_cpu_count():
    return multiprocessing.cpu_count()

def build():
    host_os = platform.system()
    config = "debug" # TODO: extend later take sys.argv[1]

    if host_os == "Linux":
        # Check for bear to maintain the LSP database
        has_bear = subprocess.run("command -v bear", shell=True, capture_output=True).returncode == 0

        make_cmd = f"make -j{get_cpu_count()} config={config}"

        full_cmd = f"bear -- {make_cmd}" if has_bear else make_cmd

        print(f"Executing: {full_cmd}")
        subprocess.call(full_cmd, shell=True)

        exit_code = subprocess.call(full_cmd, shell=True)

        if exit_code != 0:
            print(f"\n[!] BUILD FAILED: 'make' exited with code {exit_code}")
            # Signal to the OS/Terminal that the process failed
            sys.exit(exit_code)

        print("\n[+] Build Successful.")

    elif host_os == "Windows":
        print("Use MSBuild or open the generated Visual Studio solution.")

    elif host_os == "Darwim":
        print("I absolutely have no idea how you'll do it!")


if __name__ == "__main__":
    build()
