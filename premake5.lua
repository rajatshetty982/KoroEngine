-- KoroEngine - Multi-platform Build Configuration

workspace("KoroEngine")
architecture("x64")
configurations({ "Debug", "Release", "Dist" })
startproject("Sandbox")

-- Format: Debug-linux-x86_64
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- external dependency projects
include("vendor/glfw")
include("vendor/Glad")
include("vendor/imgui")

KoroDependencies = {
	"GLFW",
	"Glad",
	"imgui",
}

LinuxSystemLibraries = {
	"GL",
	"X11",
	"pthread",
	"dl",
}

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

-------------------------------------------------------------------------------
-- PROJECT: KoroEngine (Core Static Library)
-------------------------------------------------------------------------------

project("KoroEngine")
location("KoroEngine")
kind("StaticLib")
language("C++")
cppdialect("C++17")
staticruntime("On")

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
	"vendor/imgui/",
	"vendor/glm/",
})

defines({
	"GLFW_INCLUDE_NONE",
})

--
filter("configurations:Debug")
defines({ "KORO_DEBUG" })
runtime("Debug")
symbols("On")

filter("configurations:Release")
defines({ "KORO_RELEASE" })
runtime("Release")
optimize("On")

filter("configurations:Dist")
defines({ "KORO_DIST" })
runtime("Release")
optimize("Full")
--

-- Engine Dependencies
links(KoroDependencies)

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
links(LinuxSystemLibraries)

filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })

-- Not needed as we switched from shared object to static
--
-- -- for easy execution in dev
-- filter("configurations:not Dist")
-- postbuildcommands({
-- 	"{MKDIR} ../bin/" .. outputdir .. "/Sandbox/",
-- 	"{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/",
-- })

-------------------------------------------------------------------------------
-- PROJECT: Sandbox (Client Application)
-------------------------------------------------------------------------------
project("Sandbox")
location("Sandbox")
kind("ConsoleApp")
language("C++")
cppdialect("C++17")
staticruntime("On")

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
	"vendor/imgui/include",
	"vendor/glm/",
})

-- Link against the Engine (DLL/SO dependency)
links({
	"KoroEngine",
	table.unpack(KoroDependencies),
})

--
filter("configurations:Debug")
defines({ "KORO_DEBUG" })
runtime("Debug")
symbols("On")

filter("configurations:Release")
defines({ "KORO_RELEASE" })
runtime("Release")
optimize("On")

filter("configurations:Dist")
defines({ "KORO_DIST" })
runtime("Release")
optimize("Full")
--

filter("system:windows")
system("windows")
defines({ "KORO_PLATFORM_WINDOWS" })

filter("system:linux")
system("linux")
defines({ "KORO_PLATFORM_LINUX" })
-- Ensure the executable looks for KoroEngine.so in its own directory
-- linkoptions({ "-Wl,-rpath,'$ORIGIN'" })
-- Linux .so require static dependencies (GLFW/Glad) to be built with -fPIC
-- Force Position Independent Code for dynamic linking
pic("On")
links(table.unpack(LinuxSystemLibraries))

filter("system:macosx")
system("macosx")
defines({ "KORO_PLATFORM_MACOS" })
-- Look for dylibs relative to executable path
-- linkoptions({ "-Wl,-rpath,@loader_path" })

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
