#include "Game.h"

using namespace TetrisAPI;

Game::Game(const ColorManagerPtr& colorManager, const InputManagerPtr& inputManager) :
	m_colorManager(colorManager),
	m_inputManager(inputManager),
	m_grid(m_colorManager->GetEmptyCellColor()),
	m_nextBlock(GetRandomBlock())
{}

void Game::Update()
{
	if (!m_grid.BlockCanMove())
	{
		m_grid.SpawnBlock(m_nextBlock);
		m_nextBlock = GetRandomBlock();
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
