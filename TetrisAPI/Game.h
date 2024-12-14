#pragma once

#include <memory>
#include "IGame.h"
#include "IColorManager.h"
#include "IInputManager.h"
#include "Grid.h"
#include "Timer.h"
#include "IGameModeStrategy.h"

using IColorManagerPtr = std::shared_ptr<TetrisAPI::IColorManager>;
using IInputManagerPtr = std::shared_ptr<TetrisAPI::IInputManager>;
using IGameModeStrategyPtr = std::shared_ptr<TetrisAPI::IGameModeStrategy>;

namespace TetrisAPI
{
	class Game : public IGame
	{
	public:
		Game(const IColorManagerPtr& colorManager, const IInputManagerPtr& inputManager, IGameModeStrategyPtr gameModeStrategy);

		void Update() override;

		inline const Block& GetNextBlock() const override { return m_nextBlock; }
		inline const Grid& GetGrid() const override { return m_grid; }
		inline bool IsGameOver() const override { return m_gameIsOver; }
		inline bool ShowNextBlocks() const override { return m_gameModeStrategy->ShowNextBlocks(); }

	private:
		void ClearLineCheck();
		Block GetRandomBlock() const;
	private:
		IColorManagerPtr m_colorManager;
		IInputManagerPtr m_inputManager;
		IGameModeStrategyPtr m_gameModeStrategy;

		Grid m_grid;
		Block m_nextBlock;
		bool m_gameIsOver;

		Timer m_moveDownTimer;
	};
}

