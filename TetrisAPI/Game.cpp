#include "Game.h"

using namespace TetrisAPI;

Game::Game(const ColorManagerPtr& colorManager, const InputManagerPtr& inputManager) :
	m_colorManager{ colorManager },
	m_inputManager{ inputManager },
	m_grid{ m_colorManager->GetEmptyCellColor() },
	m_nextBlock{ GetRandomBlock() },
	m_moveDownTimer{ 1 }
{}

void Game::Update()
{
	if (!m_grid.BlockCanMove())
	{
		m_grid.SpawnBlock(m_nextBlock);
		m_nextBlock = GetRandomBlock();
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

Block Game::GetRandomBlock() const
{
	return Block(m_colorManager->GetRandomBlockColor(), GetRandomBlockType());
}
