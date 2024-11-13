#pragma once
#include "IInputManager.h"
#include "Block.h"

namespace TetrisAPI
{
	class IGame 
	{
	public:
		virtual void HandleInput(IInputManager* inputManager) = 0;
		virtual Block GetNextBlock() const = 0;
	};
}

