project "File_Parser"
	kind "ConsoleApp"
	language "C++"

	targetdir (solutionDir .. "/bin/" .. outputdir .. "/%{prj.name}")
	objdir (solutionDir .. "/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.h"
	}

	includedirs {
		"src",
		solutionDir .. "%{includeDirs.SPDLOG}",
		solutionDir .. "%{includeDirs.RAPIDJSON}"
	}

	libdirs {
	}

	links {
	}

	defines { }

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		staticruntime "off"
		runtime "Debug"

	filter "configurations:Debug"
		symbols "On"
	
