#pragma once

#include <memory>
#include "IGame.h"
#include "IColorManager.h"
#include "IInputManager.h"
#include "Grid.h"
#include "Observable.h"
#include "Timer.h"

using IColorManagerPtr = std::shared_ptr<TetrisAPI::IColorManager>;
using IInputManagerPtr = std::shared_ptr<TetrisAPI::IInputManager>;

namespace TetrisAPI
{
	class Game : public IGame, public Observable
	{
	public:
		Game(const IColorManagerPtr& colorManager, const IInputManagerPtr& inputManager);

		void Update();
		Block GetNextBlock() const;

	private:
		Block GetRandomBlock() const;
	private:
		IColorManagerPtr m_colorManager;
		IInputManagerPtr m_inputManager;
		
		Timer m_moveDownTimer;
		
		Grid m_grid;
		Block m_nextBlock;
	};
}

