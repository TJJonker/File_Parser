#pragma once
#include "StateMachine/State.h"
#include <StateMachine/StateManager.h>

class OverviewState : public State
{
private:
	StateManager& m_StateManager;

public:
	OverviewState(StateManager& stateManager);
	~OverviewState();

	void OnEnter(const StateData& stateData) override;
	void OnExit() override;
};

