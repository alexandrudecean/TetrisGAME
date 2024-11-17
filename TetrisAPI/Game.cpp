#include "Game.h"

using namespace TetrisAPI;

Game::Game(const IColorManagerPtr& colorManager, const IInputManagerPtr& inputManager) :
	m_colorManager{ colorManager },
	m_inputManager{ inputManager },
	m_grid{ m_colorManager->GetEmptyCellColor() },
	m_nextBlock{ GetRandomBlock() },
	m_moveDownTimer{ 1 }
{}

void Game::Update()
{
	int linesClearedCount = m_grid.ClearFullLines();
	if (linesClearedCount != 0)
	{
		NotifyAll(linesClearedCount);
		return;
	}

	if (!m_grid.BlockCanMove())
	{
		m_grid.SpawnBlock(m_nextBlock);
		m_nextBlock = std::move(GetRandomBlock());
		m_moveDownTimer.Start();
		return;
	}

	if (m_inputManager->Check(MoveDown))
	{
		m_grid.MoveDown();
		return;
	}

	if (m_moveDownTimer.ReachedThreshold())
	{
		m_grid.Move(Position::Down);
		m_moveDownTimer.Start();
	}

	if (m_inputManager->Check(Rotate))
	{
		m_grid.Rotate();
	}
	if (m_inputManager->Check(MoveLeft))
	{
		m_grid.Move(Position::Left);
	}
	else if (m_inputManager->Check(MoveLeft))
	{
		m_grid.Move(Position::Right);
	}
}

Block Game::GetNextBlock() const
{
	return m_nextBlock;
}

const Grid& Game::GetGrid() const
{
	return m_grid;
}

Block Game::GetRandomBlock() const
{
	return Block(m_colorManager->GetRandomBlockColor(), GetRandomBlockType());
}
