#pragma once

#include "PreferencesManager.h"

class LanguageLibrary
{
private:
	/// <summary>
	/// List of libraries.
	/// </summary>
	std::vector<Language>& m_Languages;

	/// <summary>
	/// Index of the active language.
	/// </summary>
	unsigned int m_ActiveLanguage;

public:
	LanguageLibrary(std::vector<Language>& langauges, unsigned int activeLanguage);
	~LanguageLibrary();

	std::string GetValue(std::string key);
	std::string GetCurrentLanguageName();
	std::string GetLanguageName(unsigned int index);
	void SetLanguage(unsigned int languageIndex);
};

