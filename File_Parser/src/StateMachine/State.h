#pragma once

class State {
public:
	struct StateData {
		unsigned int data;
	};

	virtual void OnEnter(const StateData& data = StateData{}) = 0;
	virtual void OnExit() = 0;
};