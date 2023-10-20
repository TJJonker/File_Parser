#include "pch.h"
#include "StateMachine/States/OverviewState.h"
#include "StateMachine/States/PreferencesState.h"
#include "StateMachine/States/ChangePreferenceState.h"
#include "FileHandler/FileHandler.h"
#include <Serializer/JsonSerializer.h>
#include <Serializer/PreferencesManager.h>

const std::string ConfigFilePath = "Resources/JSON/Config.json";

int main() {
	Debug::Log::Init();
	
	StateManager stateManager;

	std::map<StateManager::States, std::shared_ptr<State>> states;
	states[StateManager::States::OVERVIEW] = std::make_shared<OverviewState>(stateManager);
	states[StateManager::States::PREFERENCES] = std::make_shared<PreferencesState>(stateManager);
	states[StateManager::States::CHANGEPREFERENCE] = std::make_shared<ChangePreferenceState>(stateManager);
	stateManager.Initialize(states);


	ConfigData configData;
	std::vector<Language> languages;
	Preferences preferences;

	PreferencesManager preferencesManager(std::make_shared<JsonSerializer>());
	preferencesManager.DeserializeData(ConfigFilePath, configData, languages, preferences);
}
