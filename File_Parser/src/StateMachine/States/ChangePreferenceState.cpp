#include "pch.h"
#include "ChangePreferenceState.h"

#define LANGLIB m_StateManager.m_PreferencesWrapper.LanguageLibrary
#define PREFS m_StateManager.m_PreferencesWrapper.Preferences.Preferences
#define CONFIG m_StateManager.m_PreferencesWrapper.ConfigData
#define PREFMAN m_StateManager.m_PreferencesWrapper.PreferencesManager

/// <summary>
/// Constructor for ChangePreferenceState
/// </summary>
/// <param name="stateManager">Reference to the stateManager for switching state.</param>
ChangePreferenceState::ChangePreferenceState(StateManager& stateManager) 
	: m_StateManager(stateManager) { }

/// <summary>
/// Destructor for ChangePreferencesState.
/// </summary>
ChangePreferenceState::~ChangePreferenceState() { }

/// <summary>
/// Run upon Entering the current State.
/// </summary>
/// <param name="stateData">Additional data given fromout the previous state.</param>
void ChangePreferenceState::OnEnter(const StateData& stateData)
{
	std::string status = "Q" + std::to_string(stateData.data + 1) + "Status";

	std::string answer;
	if (stateData.data == 0) {
		answer = LANGLIB.GetCurrentLanguageName();
	}
	else if (stateData.data == 1 || stateData.data == 2) {
		answer = PREFS[stateData.data].Options[std::stoi(PREFS[stateData.data].Answer)];
	}
	else {
		answer = PREFS[stateData.data].Answer;
	} 

	LOG_TRACE("{0} {1}", LANGLIB.GetValue(status), answer);

	std::string update1 = "Q" + std::to_string(stateData.data + 1) + "Update1";
	LOG_TRACE(LANGLIB.GetValue(update1));

	std::vector<std::string> options;

	for (int i = 0; i < PREFS[stateData.data].Options.size(); i++) {
		std::string option = stateData.data != 0 ? PREFS[stateData.data].Options[i] : LANGLIB.GetLanguageName(i);
		LOG_TRACE("{0}) {1}", i + 1, option);
		options.push_back(std::to_string(i + 1));
	}

	std::string optionsString;
	for (std::string option : options)
		optionsString += ", " + option;
	optionsString.erase(0, 1);

	if(optionsString.size() > 0)
		LOG_TRACE("{0} [{1}] {2}", LANGLIB.GetValue("Cust1"), optionsString, LANGLIB.GetValue("Cust2"));  
	std::string choice = GetCertainValue(options);
	choice = choice.size() == 1 ? std::to_string(std::stoi(choice) - 1) : choice; 

	PREFS[stateData.data].Answer = choice;
	PREFMAN.SerializeData(CONFIG.PreferencesFile, m_StateManager.m_PreferencesWrapper.Preferences);
	if (stateData.data == 0)
		LANGLIB.SetLanguage(std::stoi(choice));
	

	std::string ans;
	if (stateData.data == 0) {
		ans = LANGLIB.GetCurrentLanguageName();
	}
	else if (stateData.data == 1 || stateData.data == 2) {
		ans = PREFS[stateData.data].Options[std::stoi(PREFS[stateData.data].Answer)];
	}
	else {
		ans = PREFS[stateData.data].Answer;
	}

	std::string stat = "Q" + std::to_string(stateData.data + 1) + "Update2"; 
	LOG_TRACE("{0} {1}", LANGLIB.GetValue(stat), ans);

	m_StateManager.ChangeState(StateManager::States::PREFERENCES);
}

/// <summary>
/// Run upon exiting the current state.
/// </summary>
void ChangePreferenceState::OnExit() { }

/// <summary>
/// Asks for user input and makes sure the input is valid.
/// </summary>
/// <param name="possibleOptions">Input options considered valid.</param>
/// <returns>User input.</returns>
std::string ChangePreferenceState::GetCertainValue(std::vector<std::string> possibleOptions)
{
	std::string choice;
	std::getline(std::cin, choice);

	if(choice.size() == 0)
		return GetCertainValue(possibleOptions); 

	if (possibleOptions.size() == 0)
		return choice;

	for (std::string option : possibleOptions) {
		if (choice == option)
			return choice;
	}

	LOG_TRACE(LANGLIB.GetValue("Error1")); 
	return GetCertainValue(possibleOptions); 
}
