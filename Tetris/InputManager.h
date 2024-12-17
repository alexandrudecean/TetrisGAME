/**
 * @file InputManager.h
 * @brief Declarația clasei InputManager pentru gestionarea input-urilor utilizatorului.
 *
 * Această clasă implementează interfața IInputManager și oferă funcționalități pentru
 * înregistrarea și verificarea stării tastelor apăsate.
 */

#pragma once
#include <unordered_map>
#include <vector>
#include "IInputManager.h"

 /**
  * @class InputManager
  * @brief Gestionarea input-urilor utilizatorului pentru jocul Tetris.
  *
  * InputManager permite înregistrarea și verificarea input-urilor pentru diferite tipuri definite
  * în TetrisAPI::EInputType. Stochează tastele și stările acestora și le verifică în timpul execuției.
  */

class InputManager : public TetrisAPI::IInputManager
{
public:
	/**
	* @brief Verifică dacă un anumit input este activ.
	*
	* @param inputType Tipul de input definit în TetrisAPI::EInputType.
	* @return true dacă input-ul este activ, false în caz contrar.
	*/
	bool Check(TetrisAPI::EInputType inputType);

	/**
	 * @brief Înregistrează o tastă pentru un anumit tip de input.
	 *
	 * @param inputType Tipul de input definit în TetrisAPI::EInputType.
	 * @param key Codul tastei (uint16_t) care trebuie asociată input-ului.
	 */
	void Register(TetrisAPI::EInputType inputType, uint16_t key);
private:

	/**
	 * @struct KeyState
	 * @brief Stochează starea unei taste și tastele asociate.
	 */
	struct KeyState
	{
		std::vector<uint16_t> keys;  ///< Lista codurilor tastelor asociate.
		bool lastState; ///< Starea anterioară a tastelor.
	};
private:

	bool Check(KeyState& keyState);
	bool Check(const std::vector<uint16_t>& keys);
private:
	std::unordered_map<TetrisAPI::EInputType, KeyState> m_registeredInputs;
};

