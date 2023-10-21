#pragma once

#include "PreferencesManager.h"

class LanguageLibrary
{
private:
	std::vector<Language>& m_Languages;
	unsigned int m_ActiveLanguage;

public:
	LanguageLibrary(std::vector<Language>& langauges, unsigned int activeLanguage);
	~LanguageLibrary();

	std::string GetValue(std::string key);
	std::string GetCurrentLanguageName();
	std::string GetLanguageName(unsigned int index);
	void SetLanguage(unsigned int languageIndex);
};

