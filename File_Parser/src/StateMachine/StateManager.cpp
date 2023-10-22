#include "pch.h"
#include "StateManager.h"

/// <summary>
/// Constructor for StateManager.
/// </summary>
/// <param name="preferencesWrapper">Reference to the wrapper containing all the preference data.</param>
StateManager::StateManager(PreferencesWrapper& preferencesWrapper)
	: m_CurrentState(States::OVERVIEW), m_PreferencesWrapper(preferencesWrapper) { }

/// <summary>
/// Destructor for StateManager.
/// </summary>
StateManager::~StateManager()
{
	Destroy();
}

/// <summary>
/// Intializes the StateManager.
/// </summary>
/// <param name="states">List of states.</param>
/// <param name="defaultState">Default state.</param>
void StateManager::Initialize(std::map<States, std::shared_ptr<State>> states, States defaultState)
{
	m_States = states;
	ChangeState(defaultState);
}

/// <summary>
/// Destroys and resets variables in the StateManager.
/// </summary>
void StateManager::Destroy() { }

/// <summary>
/// Changes the current state of the StateMachine.
/// </summary>
/// <param name="newState">New current state.</param>
/// <param name="data">Additional data to forward to the next state.</param>
void StateManager::ChangeState(States newState, const State::StateData& data)
{
	m_States[m_CurrentState]->OnExit();
	m_CurrentState = newState;
	m_States[m_CurrentState]->OnEnter(data);

}
