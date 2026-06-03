project("Glad")
kind("StaticLib")
language("C")
staticruntime("on")

targetdir("../../bin/" .. outputdir .. "/%{prj.name}")
objdir("../../bin-int/" .. outputdir .. "/%{prj.name}")

files({
	"include/glad/glad.h",
	"include/KHR/khrplatform.h",
	"src/glad.c",
})

includedirs({
	"include",
})

filter("system:windows")
systemversion("latest")

filter("system:linux")
pic("On")

filter("system:macosx")

filter({})
