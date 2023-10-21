#pragma once

#include "Managers/PreferencesManager.h"
#include <Managers/LanguageLibrary.h>

struct PreferencesWrapper {
	ConfigData& ConfigData;
	LanguageLibrary& LanguageLibrary;
	Preferences& Preferences;
	PreferencesManager& PreferencesManager;
};