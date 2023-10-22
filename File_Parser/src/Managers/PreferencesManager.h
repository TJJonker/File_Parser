#pragma once
#include "Serializer/ISerializer.h"

/// <summary>
/// Struct containing configurations data.
/// </summary>
struct ConfigData {
	std::string PreferencesFile;
	std::vector<std::string> LanguagesFiles;
};

/// <summary>
/// Struct containing language data.
/// </summary>
struct Language {
	std::string LanguageName;
	std::map<std::string, std::string> KeyValues;
};



class PreferencesManager
{
private:
	/// <summary>
	/// Pointer to the serialization method.
	/// </summary>
	std::shared_ptr<ISerializer> m_Serializer;

public:
	PreferencesManager(std::shared_ptr<ISerializer> serializer);

	void DeserializeData(const std::string& configFilePath, ConfigData& configOut, std::vector<Language>& languagesOut, Preferences& preferencesOut);
	void SerializeData(const std::string& preferencesPath, Preferences& preferences);
};

