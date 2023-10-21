#include "pch.h"
#include "OverviewState.h"
#include <StateMachine/StateManager.h>

#define LANGLIB m_StateManager.m_PreferencesWrapper.LanguageLibrary
#define PREFS m_StateManager.m_PreferencesWrapper.Preferences.Preferences

OverviewState::OverviewState(StateManager& stateManager)
	: m_StateManager(stateManager) { }

OverviewState::~OverviewState() { }

void OverviewState::OnEnter(const StateData& stateData)
{
	LOG_TRACE(LANGLIB.GetValue("Intro1"));
	m_StateManager.ChangeState(StateManager::States::PREFERENCES);
}

void OverviewState::OnExit()
{
}
