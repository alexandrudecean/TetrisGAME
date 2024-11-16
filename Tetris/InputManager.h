#pragma once
#include <unordered_map>
#include "IInputManager.h"

using namespace TetrisAPI;

class InputManager : public IInputManager
{
public:
	bool Check(EInputType inputType);
	void Register(EInputType inputType, uint16_t key);
private:
	struct KeyState
	{
		uint16_t key;
		bool lastState;
	};
private:
	std::unordered_map<EInputType, KeyState> m_registeredInputs;
};

