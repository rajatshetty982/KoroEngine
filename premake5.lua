workspace("KoroEngine")
architecture("x64")
configurations({ "Debug", "Release", "Dist" })
startproject("Sandbox")

-- Output directory pattern
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- OS-Specific Logic
filter("system:windows")
system("windows")
defines({ "KORO_PLATFORM_WINDOWS" })

filter("system:linux")
system("linux")
defines({ "KORO_PLATFORM_LINUX" })
-- Ensures the Sandbox finds the .so file in its own directory
linkoptions({ "-Wl,-rpath,'$ORIGIN'" })

-- not done anything for the biten fruit os
filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })
-- rpath so the executable looks for dylibs relative to itself
linkoptions({ "-Wl,-rpath,@loader_path" })

-- PROJECT: KoroEngine
project("KoroEngine")
location("KoroEngine")
kind("SharedLib")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

-- recursively find files in subfolders
files({ "KoroEngine/src/**.h", "KoroEngine/src/**.cpp" })

-- Include Path: We point to 'src' so that
-- #include "KoroEngine/Core/Core.h" works correctly.
includedirs({
	"KoroEngine/src",
	"vendor/spdlog/include",
	-- NOTE: add vendor specific libs here
})

defines({ "KORO_BUILD_DLL" })

postbuildcommands({
	"{MKDIR} ../../bin/" .. outputdir .. "/Sandbox/",
	"{COPY} %{cfg.buildtarget.relpath} ../../bin/" .. outputdir .. "/Sandbox/",
})

-- PROJECT: Sandbox
project("Sandbox")
location("Sandbox")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files({ "Sandbox/src/**.h", "Sandbox/src/**.cpp" })

-- Sync Sandbox: Must match Engine's include root
includedirs({
	"KoroEngine/src",
	"vendor/spdlog/include",
})

links({ "KoroEngine" })
