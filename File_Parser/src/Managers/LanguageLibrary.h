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

	bool GetValue(std::string& key, std::string& stringOut);
};

