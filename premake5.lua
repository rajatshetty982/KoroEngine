-- KoroEngine - Multi-platform Build Configuration

workspace("KoroEngine")
architecture("x64")
configurations({ "Debug", "Release", "Dist" })
startproject("Sandbox")

-- Format: Debug-linux-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- external dependency projects
include("vendor/glfw")
-------------------------------------------------------------------------------
-- PROJECT: KoroEngine (Core Shared Library)
-------------------------------------------------------------------------------
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
})

defines({
	"KORO_BUILD_DLL",
})

-- Engine Dependencies
links({ "GLFW" })

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

filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })
-- Look for dylibs relative to executable path
linkoptions({ "-Wl,-rpath,@loader_path" })
