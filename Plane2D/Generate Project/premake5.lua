-- premake5.lua
workspace "Plane2D"
	location "../"
	configurations {"Debug", "Release"}

project "Plane2D"
	architecture "x86"

	location "../Plane2D"
	kind "ConsoleApp"
	language "C++"

	targetdir "../%{cfg.buildcfg}"
	files {"../Plane2D/**.cpp","../Plane2D/**.h"}

filter "configurations:Debug"
	defines {"DEBUG"}
	symbols "On"

filter "configurations:Release"
	defines {"NDEBUG"}
	optimize "On"
