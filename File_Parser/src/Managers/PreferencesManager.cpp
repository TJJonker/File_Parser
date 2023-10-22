#include "pch.h"
#include "PreferencesManager.h"

/// <summary>
/// Constructor for the PreferencesManager.
/// </summary>
/// <param name="serializer">Type of serialization.</param>
PreferencesManager::PreferencesManager(std::shared_ptr<ISerializer> serializer)
	: m_Serializer(serializer) { }

/// <summary>
/// Deeserializes data and puts the data in the given structs.
/// </summary>
/// <param name="configFilePath">Path to the config file.</param>
/// <param name="configOut">Config object to copy the data to.</param>
/// <param name="languagesOut">List of language files to copy the language data to.</param>
/// <param name="preferencesOut">Preference object to copy the preferences data to.</param>
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

/// <summary>
/// Serializes the data and writes it to the preferences file.
/// </summary>
/// <param name="preferencesPath">Path to the preferences file.</param>
/// <param name="preferences">File containing the preferences data.</param>
void PreferencesManager::SerializeData(const std::string& preferencesPath, Preferences& preferences)
{
	m_Serializer->SetSource(preferencesPath);
	m_Serializer->SetPreferences(preferencesPath, preferences.Preferences);
}
