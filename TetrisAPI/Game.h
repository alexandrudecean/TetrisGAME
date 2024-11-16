#pragma once

#include <memory>
#include "IGame.h"
#include "IColorManager.h"
#include "IInputManager.h"
#include "Grid.h"
#include "Timer.h"

namespace TetrisAPI
{
	using ColorManagerPtr = std::shared_ptr<IColorManager>;
	using InputManagerPtr = std::shared_ptr<IInputManager>;
	class Game : public IGame
	{
	public:
		Game(const ColorManagerPtr& colorManager, const InputManagerPtr& inputManager);

		void Update();
		Block GetNextBlock() const;

	private:
		Block GetRandomBlock() const;
	private:
		ColorManagerPtr m_colorManager;
		InputManagerPtr m_inputManager;
		
		Timer m_moveDownTimer;
		
		Grid m_grid;
		Block m_nextBlock;
	};
}

