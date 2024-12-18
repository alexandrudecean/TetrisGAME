/**
 * @file Game.cpp
 * @brief Implementarea clasei Game care gestioneaz? logica principal? a jocului Tetris.
 *
 * Clasa Game coordoneaz? starea jocului, inclusiv mi?c?rile blocurilor, rota?iile, verificarea liniilor complete
 * ?i generarea de blocuri noi. De asemenea, notific? observatorii despre evenimentele jocului.
 */
#include "Game.h"

using namespace TetrisAPI;

/**
 * @brief Constructorul clasei Game.
 *
 * Ini?ializeaz? jocul cu managerii de culori, input ?i strategia de joc selectat?.
 *
 * @param colorManager Pointer inteligent c?tre managerul de culori.
 * @param inputManager Pointer inteligent c?tre managerul de input.
 * @param gameModeStrategy Pointer inteligent c?tre strategia de joc utilizat?.
 */
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

/**
 * @brief Actualizeaz? starea jocului la fiecare frame.
 *
 * Verific? mi?c?rile blocurilor, rota?iile, coborârea automat? ?i alte evenimente legate de joc.
 */
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

/**
 * @brief Verific? ?i elimin? liniile complete din gril?.
 *
 * Dac? sunt g?site linii complete, acestea sunt ?terse, iar observatorii sunt notifica?i.
 */
void Game::ClearLineCheck()
{
	int linesClearedCount = m_grid.ClearFullLines();
	if (linesClearedCount != 0)
	{
		NotifyLinesCleared(linesClearedCount);
	}
}

/**
 * @brief Genereaz? un bloc aleatoriu cu o culoare ?i un tip.
 *
 * @return Block Un bloc cu o culoare ?i un tip aleatoriu.
 */
Block Game::GetRandomBlock() const
{
	return { m_colorManager->GetRandomBlockColor(), GetRandomBlockType() };
}
