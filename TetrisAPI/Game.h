#pragma once

#include <memory>
#include "IGame.h"
#include "IColorManager.h"
#include "IInputManager.h"
#include "Grid.h"
#include "Timer.h"

using IColorManagerPtr = std::shared_ptr<TetrisAPI::IColorManager>;
using IInputManagerPtr = std::shared_ptr<TetrisAPI::IInputManager>;

namespace TetrisAPI
{
	class Game : public IGame
	{
	public:
		Game(const IColorManagerPtr& colorManager, const IInputManagerPtr& inputManager);

		void Update();
		Block GetNextBlock() const;
		const Grid& GetGrid() const;

	private:
		void ClearLineCheck();
		Block GetRandomBlock() const;
	private:
		IColorManagerPtr m_colorManager;
		IInputManagerPtr m_inputManager;
		
		Grid m_grid;
		Block m_nextBlock;
		
		Timer m_moveDownTimer;
		
	};
}

