#pragma once
#include <unordered_map>
#include <vector>
#include "IInputManager.h"

class InputManager : public TetrisAPI::IInputManager
{
public:
	bool Check(TetrisAPI::EInputType inputType);
	void Register(TetrisAPI::EInputType inputType, uint16_t key);
private:
	struct KeyState
	{
		std::vector<uint16_t> keys;
		bool lastState;
	};
private:
	bool Check(KeyState& keyState);
	bool Check(const std::vector<uint16_t>& keys);
private:
	std::unordered_map<TetrisAPI::EInputType, KeyState> m_registeredInputs;
};

