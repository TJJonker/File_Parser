#include "pch.h"
#include "PreferencesState.h"

PreferencesState::PreferencesState(StateManager& stateManager)
	: m_StateManager(stateManager) { }

PreferencesState::~PreferencesState() { }

void PreferencesState::OnEnter(const StateData& stateData)
{
	LOG_TRACE("Welcome to the Preferences state.");
}

void PreferencesState::OnExit()
{
}
