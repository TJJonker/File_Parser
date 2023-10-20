#include "pch.h"
#include "StateMachine/States/OverviewState.h"
#include "StateMachine/States/PreferencesState.h"
#include "StateMachine/States/ChangePreferenceState.h"
#include <rapidjson.h>
#include <document.h>
#include <filewritestream.h>
#include <filereadstream.h>
#include "FileHandler/FileHandler.h"


struct ConfigData {
	std::string PreferencesFile;
	std::map<std::string, std::string> LanguagesFiles;
};

struct Languages {
	std::string LanguageName;
	std::map<std::string, std::string> KeyValues;
};


bool ReadConfigFromJSON(const std::string& filePath, ConfigData& configDataOut);

int main() {
	Debug::Log::Init();
	
	StateManager stateManager;

	std::map<StateManager::States, std::shared_ptr<State>> states;
	states[StateManager::States::OVERVIEW] = std::make_shared<OverviewState>(stateManager);
	states[StateManager::States::PREFERENCES] = std::make_shared<PreferencesState>(stateManager);
	states[StateManager::States::CHANGEPREFERENCE] = std::make_shared<ChangePreferenceState>(stateManager);
	stateManager.Initialize(states);


	//ConfigData data;
	//ReadConfigFromJSON("Resources/JSON/Config.json", data);

}

bool ReadConfigFromJSON(const std::string& filePath, ConfigData& configDataOut) {

	// File openinig
	FILE* fp = 0;
	fopen_s(&fp, filePath.c_str(), "rb");

	// File reading
	char readBuffer[65536];
	rapidjson::FileReadStream fss(fp, readBuffer, sizeof(readBuffer));
	
	// Place everything into a document
	rapidjson::Document document;
	document.ParseStream(fss);
	
	// Search for preference
	rapidjson::Value& preferenceFile = document["PreferencesFile"];
	std::string filename = preferenceFile.GetString();

	fclose(fp);
	
	return true;

}