#include "pch.h"
#include "PreferencesManager.h"

PreferencesManager::PreferencesManager(std::shared_ptr<ISerializer> serializer)
	: m_Serializer(serializer) { }

void PreferencesManager::DeserializeData(const std::string& configFilePath, ConfigData& configOut, std::vector<Language>& languagesOut, Preferences& preferencesOut)
{

	// Config file
	m_Serializer->SetSource(configFilePath);
	m_Serializer->GetStringAttribute("PreferencesFile", configOut.PreferencesFile);
	m_Serializer->GetStringVectorAttribute("LanguagesFiles", configOut.LanguagesFiles);

	// Preferences
	m_Serializer->SetSource(configOut.PreferencesFile);
	m_Serializer->GetPreferences(preferencesOut.Preferences);

	// Language files
	for (int i = 0; i < configOut.LanguagesFiles.size(); i++) {
		m_Serializer->SetSource(configOut.LanguagesFiles[i]);
		Language language;
		m_Serializer->GetStringAttribute("Language", language.LanguageName);
		m_Serializer->GetStringStringMapAttribute("LanguageKeyValues", language.KeyValues);
		languagesOut.push_back(language);
	}
}

void PreferencesManager::SerializeData(const std::string& preferencesPath, Preferences& preferences)
{
	m_Serializer->SetSource(preferencesPath);
	m_Serializer->SetPreferences(preferencesPath, preferences.Preferences);
}
