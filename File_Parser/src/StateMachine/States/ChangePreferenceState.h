#pragma once
#include "StateMachine/State.h"
#include <StateMachine/StateManager.h>

class ChangePreferenceState : public State
{
private:
	StateManager& m_StateManager;

public:
	ChangePreferenceState(StateManager& stateManager);
	~ChangePreferenceState();

	void OnEnter(const StateData& stateData) override;
	void OnExit() override;

private:
	std::string GetCertainValue(std::vector<std::string> possibleOptions);
};

