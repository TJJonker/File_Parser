#include "pch.h"
#include "LanguageLibrary.h"

/// <summary>
/// Constructor for the LanguageLibrary.
/// </summary>
/// <param name="languages">vector of language files.</param>
/// <param name="activeLanguage">Index of the currently active language.</param>
LanguageLibrary::LanguageLibrary(std::vector<Language>& languages, unsigned int activeLanguage)
	:m_Languages(languages), m_ActiveLanguage(activeLanguage - 1) { }

/// <summary>
/// Destructor for the LanguageLibrary.
/// </summary>
LanguageLibrary::~LanguageLibrary() { }

/// <summary>
/// Get the value out of the langauge file. 
/// </summary>
/// <param name="key">Key of the language value.</param>
/// <returns>String if successfull, Empty string when failed.</returns>
std::string LanguageLibrary::GetValue(std::string key)
{
	if (!m_Languages[m_ActiveLanguage].KeyValues.count(key)) {
		LOG_WARNING("key '{0}' is not a valid entry in the {1} language file.", key, m_Languages[m_ActiveLanguage].LanguageName);
		return "";
	}

	return m_Languages[m_ActiveLanguage].KeyValues[key];
}

/// <summary>
/// Returns name of the active language library.
/// </summary>
/// <returns>The name of the active language library.</returns>
std::string LanguageLibrary::GetCurrentLanguageName()
{
	return m_Languages[m_ActiveLanguage].LanguageName;
}

/// <summary>
/// Returns the name of the indexed language library.
/// </summary>
/// <param name="index">Index of the language library.</param>
/// <returns>The name of the indexed language library.</returns>
std::string LanguageLibrary::GetLanguageName(unsigned int index)
{
	if (index >= m_Languages.size()) {
		LOG_WARNING("Language index out of range.");
		return "";
	}

	return m_Languages[index].LanguageName;
}

/// <summary>
/// Sets the currently active langauge.
/// </summary>
/// <param name="languageIndex">Index of the newly active language.</param>
void LanguageLibrary::SetLanguage(unsigned int languageIndex)
{
	m_ActiveLanguage = languageIndex;
}
