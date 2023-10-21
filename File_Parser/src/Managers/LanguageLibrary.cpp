#include "pch.h"
#include "LanguageLibrary.h"

LanguageLibrary::LanguageLibrary(std::vector<Language>& languages, unsigned int activeLanguage)
	:m_Languages(languages), m_ActiveLanguage(activeLanguage - 1) { }

LanguageLibrary::~LanguageLibrary() { }

std::string LanguageLibrary::GetValue(std::string key)
{
	if (!m_Languages[m_ActiveLanguage].KeyValues.count(key)) {
		LOG_WARNING("key '{0}' is not a valid entry in the {1} language file.", key, m_Languages[m_ActiveLanguage].LanguageName);
		return "";
	}

	return m_Languages[m_ActiveLanguage].KeyValues[key];
}

std::string LanguageLibrary::GetCurrentLanguageName()
{
	return m_Languages[m_ActiveLanguage].LanguageName;
}

std::string LanguageLibrary::GetLanguageName(unsigned int index)
{
	if (index >= m_Languages.size()) {
		LOG_WARNING("Language index out of range.");
		return "";
	}

	return m_Languages[index].LanguageName;
}

void LanguageLibrary::SetLanguage(unsigned int languageIndex)
{
	m_ActiveLanguage = languageIndex;
}
