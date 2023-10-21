#include "pch.h"
#include "StateMachine/States/OverviewState.h"
#include "StateMachine/States/PreferencesState.h"
#include "StateMachine/States/ChangePreferenceState.h"
#include <Serializer/JsonSerializer.h>

const std::string ConfigFilePath = "Resources/JSON/Config.json";

int main() {
	Debug::Log::Init();

	ConfigData configData; 
	Preferences preferences; 
	PreferencesManager preferencesManager(std::make_shared<JsonSerializer>()); 

	std::vector<Language> languages;  
	preferencesManager.DeserializeData(ConfigFilePath, configData, languages, preferences); 
	LanguageLibrary languageLibrary(languages, std::stoi(preferences.Preferences[0].Answer));

	PreferencesWrapper preferencesWrapper{ configData, languageLibrary, preferences, preferencesManager };	
	StateManager stateManager(preferencesWrapper);

	std::map<StateManager::States, std::shared_ptr<State>> states;
	states[StateManager::States::OVERVIEW] = std::make_shared<OverviewState>(stateManager);
	states[StateManager::States::PREFERENCES] = std::make_shared<PreferencesState>(stateManager);
	states[StateManager::States::CHANGEPREFERENCE] = std::make_shared<ChangePreferenceState>(stateManager);
	stateManager.Initialize(states);


}
