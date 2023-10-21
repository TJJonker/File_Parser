#include "pch.h"
#include "PreferencesState.h"

#define LANGLIB m_StateManager.m_PreferencesWrapper.LanguageLibrary
#define PREFS m_StateManager.m_PreferencesWrapper.Preferences.Preferences

PreferencesState::PreferencesState(StateManager& stateManager)
	: m_StateManager(stateManager) { }

PreferencesState::~PreferencesState() { }

void PreferencesState::OnEnter(const StateData& stateData)
{
	LOG_TRACE("");
	LOG_TRACE(LANGLIB.GetValue("Pref1"));

	for (int i = 0; i < PREFS.size(); i++) {
		std::string q = "Q" + std::to_string(i + 1);

		std::string answer;
		if (i == 0) {
			answer = LANGLIB.GetCurrentLanguageName();
		}
		else if (i == 1 || i == 2) {
			answer = PREFS[i].Options[std::stoi(PREFS[i].Answer)]; 
		}
		else {
			answer = PREFS[i].Answer;
		}

		LOG_TRACE("{0}) {1}: {2}", i + 1, LANGLIB.GetValue(q), answer);
	}

	LOG_TRACE("{0} [1,2,3,4] {1}", LANGLIB.GetValue("Cust1"), LANGLIB.GetValue("Cust2"));

	std::string choice = GetCertainValue({ "1", "2", "3", "4" });

	StateData data{ std::stoi(choice) - 1 };
	m_StateManager.ChangeState(StateManager::States::CHANGEPREFERENCE, data);
}

void PreferencesState::OnExit() { }

std::string PreferencesState::GetCertainValue(std::vector<std::string> possibleOptions)
{
	std::string choice;
	std::cin >> choice;

	for (std::string option : possibleOptions) {
		if (choice == option)
			return choice;
	}

	LOG_TRACE(LANGLIB.GetValue("Error1"));
	return GetCertainValue(possibleOptions);
}
