#pragma once
#include <string>
#include <vector>
#include <map>

// Hacky... Shouldn't be here...
struct Preferences {
	struct Preference {
		std::string Question;
		std::string Answer;
		std::vector<std::string> Options;
	};

	std::vector<Preference> Preferences;
};


#define LOGANDRETURN(...) { LOG_WARNING(__VA_ARGS__); return false; }

class ISerializer {
public:
	virtual bool SetSource(const std::string& filePath) = 0;
	virtual bool GetStringAttribute(const std::string& attributeName, std::string& valueOut) = 0;
	virtual bool GetIntAttribute(const std::string& attributeName, int& valueOut) = 0;
	virtual bool GetStringVectorAttribute(const std::string& attributeName, std::vector<std::string>& valueOut) = 0;
	virtual bool GetStringStringMapAttribute(const std::string& attributeName, std::map<std::string, std::string>& valueOut) = 0;

	// Hacky as well...
	virtual bool GetPreferences(std::vector<Preferences::Preference>& valueOut) = 0;
};