#include "pch.h"
#include "LanguageLibrary.h"

LanguageLibrary::LanguageLibrary(std::vector<Language>& languages, unsigned int activeLanguage)
	:m_Languages(languages), m_ActiveLanguage(activeLanguage) { }

LanguageLibrary::~LanguageLibrary() { }

bool LanguageLibrary::GetValue(std::string& key, std::string& stringOut)
{
	if (!m_Languages[m_ActiveLanguage].KeyValues.count(key))
		LOGANDRETURN("key '{0}' is not a valid entry in the {1} language file.", key, m_Languages[m_ActiveLanguage].LanguageName);

	stringOut = m_Languages[m_ActiveLanguage].KeyValues[key];
	return true;
}
