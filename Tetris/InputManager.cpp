#include <raylib.h>
#include "InputManager.h"

bool InputManager::Check(TetrisAPI::EInputType inputType)
{
    auto& keyState = m_registeredInputs.at(inputType);
    bool currentState = IsKeyDown(keyState.key);
    bool validInput = false;
    if (currentState == true && keyState.lastState != currentState)
    {
        validInput = true;
    }
    keyState.lastState = currentState;
    return validInput;
}

void InputManager::Register(TetrisAPI::EInputType inputType, uint16_t key)
{
    m_registeredInputs[inputType] = { key, false };
}
