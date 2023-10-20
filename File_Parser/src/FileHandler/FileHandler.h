#pragma once
class FileHandler
{
public:
	static bool ReadFile(std::string& filePath, std::string& dataOut);
	static bool WriteFile(std::string& filePath, const char* data);
};

