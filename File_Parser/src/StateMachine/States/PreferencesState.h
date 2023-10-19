#pragma once
#include "StateMachine/State.h"
#include <StateMachine/StateManager.h>

class PreferencesState : public State
{
private:
	StateManager& m_StateManager;

public:
	PreferencesState(StateManager& stateManager);
	~PreferencesState();

	void OnEnter(const StateData& stateData) override;
	void OnExit() override;
};

