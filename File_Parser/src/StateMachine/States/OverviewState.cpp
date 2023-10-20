#include "pch.h"
#include "OverviewState.h"
#include <StateMachine/StateManager.h>

OverviewState::OverviewState(StateManager& stateManager)
	: m_StateManager(stateManager) { }

OverviewState::~OverviewState() { }

void OverviewState::OnEnter(const StateData& stateData)
{
	LOG_TRACE("Welcome to the UserPreferator, where all your UserPrefs can be set.");
	LOG_TRACE("Enter 'x' at any time to exit the program.");
	LOG_TRACE("Your current preferences are:");
	
	//std::string something;
	//std::cin >> something;

	//m_StateManager.ChangeState(StateManager::States::PREFERENCES);
}

void OverviewState::OnExit()
{
}
