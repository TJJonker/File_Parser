#pragma once

#include "Managers/PreferencesManager.h"
#include <Managers/LanguageLibrary.h>

/// <summary>
/// Struct containing all the preferences related objects.
/// </summary>
struct PreferencesWrapper {
	ConfigData& ConfigData;
	LanguageLibrary& LanguageLibrary;
	Preferences& Preferences;
	PreferencesManager& PreferencesManager;
};