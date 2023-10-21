#pragma once
#include "ISerializer.h"
#include <document.h>
class JsonSerializer : public ISerializer
{
private:
	rapidjson::Document m_Document;

public:
	bool SetSource(const std::string& data) override;
	bool GetStringAttribute(const std::string& attributeName, std::string& valueOut) override;
	bool GetIntAttribute(const std::string& attributeName, int& valueOut) override;
	bool GetStringVectorAttribute(const std::string& attributeName, std::vector<std::string>& valueOut) override;
	bool GetStringStringMapAttribute(const std::string& attributeName, std::map<std::string, std::string>& valueOut) override;

	// Hacky
	bool GetPreferences(std::vector<Preferences::Preference>& valueOut) override;
	bool SetPreferences(const std::string& filePath, std::vector<Preferences::Preference>& value) override;
};

