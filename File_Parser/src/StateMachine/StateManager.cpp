#include "pch.h"
#include "StateManager.h"

StateManager::StateManager(PreferencesWrapper& preferencesWrapper)
	: m_CurrentState(States::OVERVIEW), m_PreferencesWrapper(preferencesWrapper) { }

StateManager::~StateManager()
{
	Destroy();
}

void StateManager::Initialize(std::map<States, std::shared_ptr<State>> states, States defaultState)
{
	m_States = states;
	ChangeState(defaultState);
}

void StateManager::Destroy() { }

void StateManager::ChangeState(States newState, const State::StateData& data)
{
	m_States[m_CurrentState]->OnExit();
	m_CurrentState = newState;
	m_States[m_CurrentState]->OnEnter(data);

}
