#pragma once
#include "State.h"
#include <Managers/PreferencesWrapper.h>

class StateManager
{
public:
	/// <summary>
	/// Overview of possible states to switch to.
	/// </summary>
	enum class States {
		OVERVIEW,
		PREFERENCES,
		CHANGEPREFERENCE,
	};

	/// <summary>
	/// Reference to the wrapper containing the preferences data.
	/// </summary>
	PreferencesWrapper& m_PreferencesWrapper;

private:
	/// <summary>
	/// List of states.
	/// </summary>
	std::map<States, std::shared_ptr<State>> m_States;

	/// <summary>
	/// Currently active state.
	/// </summary>
	States m_CurrentState;

public:
	StateManager(PreferencesWrapper& preferencesWrapper);
	~StateManager();

	void Initialize(std::map<States, std::shared_ptr<State>> states, States defaultState = States::OVERVIEW);
	void Destroy();

	void ChangeState(States newState, const State::StateData& data = State::StateData{});
};

