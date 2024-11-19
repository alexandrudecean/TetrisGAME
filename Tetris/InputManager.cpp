#include <raylib.h>
#include "InputManager.h"

bool InputManager::Check(TetrisAPI::EInputType inputType)
{
    auto& keyState = m_registeredInputs.at(inputType);
    return Check(keyState);
}

void InputManager::Register(TetrisAPI::EInputType inputType, uint16_t key)
{
    auto it = m_registeredInputs.find(inputType);

    if (it == m_registeredInputs.end())
    {
        m_registeredInputs[inputType] = { {key}, false };
        return;
    }

    it->second.keys.emplace_back(key);
}

bool InputManager::Check(KeyState& keyState)
{
    bool currentState = Check(keyState.keys);
    bool validInput = false;
    if (currentState == true && keyState.lastState != currentState)
    {
        validInput = true;
        keyState.lastState = currentState;
        return true;
    }
    keyState.lastState = currentState;
    return false;
}

bool InputManager::Check(const std::vector<uint16_t>& keys)
{
    for (const uint16_t key : keys)
    {
        if (IsKeyDown(key))
            return true;
    }
    return false;
}
