#pragma once
#include <unordered_map>
#include "IInputManager.h"

class InputManager : public TetrisAPI::IInputManager
{
public:
	bool Check(TetrisAPI::EInputType inputType);
	void Register(TetrisAPI::EInputType inputType, uint16_t key);
private:
	struct KeyState
	{
		uint16_t key;
		bool lastState;
	};
private:
	std::unordered_map<TetrisAPI::EInputType, KeyState> m_registeredInputs;
};

