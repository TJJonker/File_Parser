#include "pch.h"
#include "OverviewState.h"
#include <StateMachine/StateManager.h>

#define LANGLIB m_StateManager.m_PreferencesWrapper.LanguageLibrary
#define PREFS m_StateManager.m_PreferencesWrapper.Preferences.Preferences

/// <summary>
/// Constructor for OverviewState.
/// </summary>
/// <param name="stateManager">Reference to the stateManager for switching state.</param>
OverviewState::OverviewState(StateManager& stateManager)
	: m_StateManager(stateManager) { }

/// <summary>
/// Destructor for OverviewState.
/// </summary>
OverviewState::~OverviewState() { }

/// <summary>
/// Run upon Entering the current State.
/// </summary>
/// <param name="stateData">Additional data given fromout the previous state.</param>
void OverviewState::OnEnter(const StateData& stateData)
{
	LOG_TRACE(LANGLIB.GetValue("Intro1"));
	m_StateManager.ChangeState(StateManager::States::PREFERENCES);
}

/// <summary>
/// Run upon exiting the current state.
/// </summary>
void OverviewState::OnExit()
{
}
