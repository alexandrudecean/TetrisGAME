#include "Game.h"

using namespace TetrisAPI;

Game::Game(const IColorManagerPtr& colorManager, const IInputManagerPtr& inputManager, IGameModeStrategyPtr gameModeStrategy) :
	m_colorManager{ colorManager },
	m_inputManager{ inputManager },
	m_grid{ m_colorManager->GetEmptyCellColor() },
	m_nextBlock{ std::move(GetRandomBlock()) },
	m_gameIsOver{ false },
	m_gameModeStrategy{ std::move(gameModeStrategy) },
	m_moveDownTimer{ m_gameModeStrategy->GetMoveDownInterval() }
{
}

void Game::Update()
{
	if (m_gameIsOver)
		return;

	if (!m_grid.BlockCanMove())
	{
		ClearLineCheck();
		if (!m_grid.SpawnBlock(m_nextBlock))
		{
			m_gameIsOver = true;
			NotifyGameOver();
			return;
		}
		m_nextBlock = std::move(GetRandomBlock());
		m_moveDownTimer.Start();
	}

	if (m_inputManager->Check(MoveDown))
	{
		m_grid.MoveDown();
		NotifyMoveDownBlock();
		return;
	}

	if (m_moveDownTimer.ReachedThreshold())
	{
		m_grid.Move(Position::Down);
		if (!m_grid.BlockCanMove())
			NotifyMoveDownBlock();
		m_moveDownTimer.Start();
	}

	if (m_inputManager->Check(Rotate))
	{
		if (m_grid.Rotate())
			NotifyRotateBlock();
	}

	if (m_inputManager->Check(MoveLeft))
	{
		m_grid.Move(Position::Left);
	}
	else if (m_inputManager->Check(MoveRight))
	{
		m_grid.Move(Position::Right);
	}
}

void Game::ClearLineCheck()
{
	int linesClearedCount = m_grid.ClearFullLines();
	if (linesClearedCount != 0)
	{
		NotifyLinesCleared(linesClearedCount);
	}
}

Block Game::GetRandomBlock() const
{
	return { m_colorManager->GetRandomBlockColor(), GetRandomBlockType() };
}
