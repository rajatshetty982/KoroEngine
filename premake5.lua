workspace("KoroEngine")
architecture("x64")
configurations({ "Debug", "Release", "Dist" })
startproject("Sandbox")

-- Define base output path
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Global platform detection
filter("system:windows")
system("windows")
defines({ "KORO_PLATFORM_WINDOWS" })

filter("system:linux")
system("linux")
defines({ "KORO_PLATFORM_LINUX" })
linkoptions({ "-Wl,-rpath,'$ORIGIN'" })

-- PROJECT: KoroEngine
project("KoroEngine")
location("KoroEngine")
kind("SharedLib")
language("C++")
cppdialect("C++17")
staticruntime("off")

targetdir("bin/" .. outputdir .. "/%{prj.name}")
objdir("bin-int/" .. outputdir .. "/%{prj.name}")

files({ "KoroEngine/src/**.h", "KoroEngine/src/**.cpp" })
includedirs({ "KoroEngine/src", "libs/spdlog/include" })
defines({ "KORO_BUILD_DLL" })

-- UNIVERSAL AUTOMATION:
-- This works on Windows (.dll) and Linux (.so)
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
includedirs({ "KoroEngine/src", "libs/spdlog/include" })

links({ "KoroEngine" })
