-- KoroEngine - Multi-platform Build Configuration

workspace("KoroEngine")
architecture("x64")
configurations({ "debug", "release", "dist" })
startproject("Sandbox")

-- Format: Debug-linux-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- external dependency projects
include("vendor/glfw")
include("vendor/Glad")

-------------------------------------------------------------------------------
-- PROJECT: KoroEngine (Core Shared Library)
-------------------------------------------------------------------------------

filter("configurations:debug")
defines({ "KORO_DEBUG" }) -- Note the single quotes wrapping the double quotes!
symbols("On")

filter("configurations:release")
defines({ "KORO_RELEASE" })
optimize("On")

filter("configurations:dist")
defines({ "KORO_DIST" })
optimize("Full")

filter({ "system:macosx" })
buildoptions({
	"-Wall",
	"-Wextra",
	"-Wpedantic",
})

filter({ "system:linux" })
buildoptions({
	"-Wall",
	"-Wextra",
	"-Wpedantic",
})

filter({})
------
---
project("KoroEngine")
location("KoroEngine")
kind("SharedLib")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

-- Precompiled Header Configuration
pchheader("koropch.h")
pchsource("KoroEngine/src/koropch.cpp")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
})

includedirs({
	"%{prj.name}/src",
	"vendor/spdlog/include",
	"vendor/glfw/include",
	"vendor/Glad/include",
})

defines({
	"KORO_BUILD_DLL",
	"GLFW_INCLUDE_NONE",
})

-- Engine Dependencies
links({ "GLFW" })
links({ "Glad" })

-- Platform-Specific Configuration
filter("system:windows")
system("windows")
defines({ "KORO_PLATFORM_WINDOWS" })
-- Windows system libs required for graphics/windowing
links({ "gdi32", "user32", "shell32" })

filter("system:linux")
system("linux")
defines({ "KORO_PLATFORM_LINUX" })
-- Standard Linux development libraries
-- core display drivers
links({ "GL", "X11", "pthread", "dl" })

filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })

-- for easy execution in dev
filter("configurations:not Dist")
postbuildcommands({
	"{MKDIR} ../bin/" .. outputdir .. "/Sandbox/",
	"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/",
})

-------------------------------------------------------------------------------
-- PROJECT: Sandbox (Client Application)
-------------------------------------------------------------------------------
project("Sandbox")
location("Sandbox")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files({
	"%{prj.name}/src/**.h",
	"%{prj.name}/src/**.cpp",
})

includedirs({
	"KoroEngine/src",
	"vendor/spdlog/include",
	"vendor/glfw/include",
	"vendor/Glad/include",
})

-- Link against the Engine (DLL/SO dependency)
links({ "KoroEngine" })

filter("system:windows")
system("windows")
defines({ "KORO_PLATFORM_WINDOWS" })

filter("system:linux")
system("linux")
defines({ "KORO_PLATFORM_LINUX" })
-- Ensure the executable looks for KoroEngine.so in its own directory
linkoptions({ "-Wl,-rpath,'$ORIGIN'" })
-- Linux .so require static dependencies (GLFW/Glad) to be built with -fPIC
-- Force Position Independent Code for dynamic linking
pic("On")

filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })
-- Look for dylibs relative to executable path
linkoptions({ "-Wl,-rpath,@loader_path" })

filter("configurations:debug")
defines({ "KORO_DEBUG" }) -- Note the single quotes wrapping the double quotes!
symbols("On")

filter("configurations:release")
defines({ "KORO_RELEASE" })
optimize("On")

filter("configurations:dist")
defines({ "KORO_DIST" })
optimize("Full")

filter({ "system:macosx" })
buildoptions({
	"-Wall",
	"-Wextra",
	"-Wpedantic",
})

filter({ "system:linux" })
buildoptions({
	"-Wall",
	"-Wextra",
	"-Wpedantic",
})

filter({})
