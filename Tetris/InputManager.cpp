/**
 * @file InputManager.cpp
 * @brief Implementarea clasei InputManager pentru gestionarea input-urilor utilizatorului.
 */
#include <raylib.h>
#include "InputManager.h"

 /**
 * @brief Verifică dacă input-ul asociat unui anumit tip este activ.
 *
 * @details Această funcție folosește tipul de input înregistrat și verifică
 * starea curentă a tastelor asociate acestuia.
 *
 * @param inputType Tipul de input definit în TetrisAPI::EInputType.
 * @return true dacă input-ul este activ, false în caz contrar.
 *
 * @see Register()
 */

bool InputManager::Check(TetrisAPI::EInputType inputType)
{
    auto& keyState = m_registeredInputs.at(inputType);
    return Check(keyState);
}

/**
 * @brief Înregistrează o tastă pentru un anumit tip de input.
 *
 * @details Dacă tipul de input nu este deja înregistrat, acesta va fi adăugat.
 * Dacă există, tasta este adăugată la lista existentă de taste.
 *
 * @param inputType Tipul de input definit în TetrisAPI::EInputType.
 * @param key Codul tastei (uint16_t) care trebuie asociată input-ului.
 *
 * @see Check()
 */

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

/**
 * @brief Verifică starea actuală a unei taste înregistrate.
 *
 * @param keyState Referință la starea tastei.
 * @return true dacă input-ul este valid (activat), false în caz contrar.
 */
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

/**
 * @brief Verifică dacă oricare dintre tastele din lista dată este apăsată.
 *
 * @param keys Vector de coduri de taste.
 * @return true dacă cel puțin o tastă este apăsată, false în caz contrar.
 */
bool InputManager::Check(const std::vector<uint16_t>& keys)
{
    for (const uint16_t key : keys)
    {
        if (IsKeyDown(key))
            return true;
    }
    return false;
}
