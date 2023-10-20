workspace "Parser_Program"
	architecture "x64"
	startproject "Chat_Client" 

	configurations {
		"Debug"
	}

solutionDir = "%{wks.location}/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "File_Parser"

includeDirs = {}
includeDirs["SPDLOG"] = "Vendor/spdlog/include"
includeDirs["RAPIDJSON"] = "Vendor/rapidjson"

libraryDirs = {}


