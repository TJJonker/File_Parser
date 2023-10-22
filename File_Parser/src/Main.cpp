#include "pch.h"
#include "StateMachine/States/OverviewState.h"
#include "StateMachine/States/PreferencesState.h"
#include "StateMachine/States/ChangePreferenceState.h"
#include <Serializer/JsonSerializer.h>
#include <Serializer/XmlSerializer.h>

/// Switch comment these two lines
//const std::string ConfigFilePath = "Resources/JSON/Config.json";
const std::string ConfigFilePath = "Resources/XML/Config.xml";

int main() {
	Debug::Log::Init();

	ConfigData configData; 
	Preferences preferences; 

	/// Switch comment these two lines
	//PreferencesManager preferencesManager(std::make_shared<JsonSerializer>()); 
	PreferencesManager preferencesManager(std::make_shared<XmlSerializer>());

	std::vector<Language> languages;  
	preferencesManager.DeserializeData(ConfigFilePath, configData, languages, preferences); 
	LanguageLibrary languageLibrary(languages, std::stoi(preferences.Preferences[0].Answer) + 1);

	PreferencesWrapper preferencesWrapper{ configData, languageLibrary, preferences, preferencesManager };	
	StateManager stateManager(preferencesWrapper);

	std::map<StateManager::States, std::shared_ptr<State>> states;
	states[StateManager::States::OVERVIEW] = std::make_shared<OverviewState>(stateManager);
	states[StateManager::States::PREFERENCES] = std::make_shared<PreferencesState>(stateManager);
	states[StateManager::States::CHANGEPREFERENCE] = std::make_shared<ChangePreferenceState>(stateManager);
	stateManager.Initialize(states);
}
