# import os
import subprocess
import platform

def run_premake():
    system = platform.system()
    
    if system == "Linux":
        premake_path = "vendor/bin/premake/premake5"
    elif system == "Windows":
        premake_path = "vendor\\bin\\premake\\premake5.exe"
    elif system == "Darwin": 
        premake_path = "vendor/bin/premake/mac/premake5"
    else:
        print(f"Unsupported OS: {system}")
        return

    print(f"Running Premake for {system}...")
    
    # You can change this to 'vs2022' on Windows if needed
    action = "gmake" if system != "Windows" else "vs2022"
    
    try:
        subprocess.check_call([premake_path, action])
        print("\nProject generation successful!")
    except subprocess.CalledProcessError as e:
        print(f"\nError: Premake failed with exit code {e.returncode}")

if __name__ == "__main__":
    run_premake()
