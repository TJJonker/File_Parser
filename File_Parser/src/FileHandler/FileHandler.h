#pragma once
class FileHandler
{
public:
	static bool ReadFile(const std::string& filePath, std::string& dataOut);
	static bool WriteFile(const std::string& filePath, const char* data);
};

