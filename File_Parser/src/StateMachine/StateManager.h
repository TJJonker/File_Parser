#pragma once
#include "State.h"

class StateManager
{
public:
	enum class States {
		OVERVIEW,
		PREFERENCES,
		CHANGEPREFERENCE,
	};

private:
	std::map<States, std::shared_ptr<State>> m_States;
	States m_CurrentState;

public:
	StateManager();
	~StateManager();

	void Initialize(std::map<States, std::shared_ptr<State>> states, States defaultState = States::OVERVIEW);
	void Destroy();

	void ChangeState(States newState, const State::StateData& data = State::StateData{});
};
