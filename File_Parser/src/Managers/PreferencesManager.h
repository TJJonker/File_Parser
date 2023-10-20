#pragma once
#include "Serializer/ISerializer.h"

struct ConfigData {
	std::string PreferencesFile;
	std::vector<std::string> LanguagesFiles;
};

struct Language {
	std::string LanguageName;
	std::map<std::string, std::string> KeyValues;
};



class PreferencesManager
{
private:
	std::shared_ptr<ISerializer> m_Serializer;

public:
	PreferencesManager(std::shared_ptr<ISerializer> serializer);

	void DeserializeData(const std::string& configFilePath, ConfigData& configOut, std::vector<Language>& languagesOut, Preferences& preferencesOut);
	void SerializeData(const std::string& configFilePath, const ConfigData& configOut, const Language& languagesOut, const Preferences& preferencesOut);
};

