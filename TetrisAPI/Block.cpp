/**
 * @file Block.cpp
 * @brief Implementarea clasei Block, reprezentând blocurile jocului Tetris ?i comportamentul acestora.
 *
 * Clasa Block gestioneaz? rota?iile ?i pozi?iile fiec?rui tip de bloc din jocul Tetris.
 */
#include "Block.h"

using namespace TetrisAPI;


/**
 * @brief Constructorul clasei Block.
 *
 * Ini?ializeaz? un bloc cu o culoare ?i un tip specific, configurând rota?iile posibile.
 *
 * @param color Culoarea blocului.
 * @param blockType Tipul blocului (I, L, J, Z, S, T, O).
 */
Block::Block(const Color& color, EBlockType blockType) :
	m_color{ color },
	m_blockType{ blockType },
	m_indexState{ 0 }
{
	switch (m_blockType)	
	{
	case I:
		IBlock();
		break;
	case L:
		LBlock();
		break;
	case J:
		JBlock();
		break;
	case Z:
		ZBlock();
		break;
	case S:
		SBlock();
		break;
	case T:
		TBlock();
		break;
	case O:
		OBlock();
		break;
	default:
		break;
	}
}

/**
 * @brief Rote?te blocul în sens orar, trecând la urm?toarea stare de rota?ie.
 */
void Block::Rotate()
{
	m_indexState++;
	if (m_indexState == m_rotation.size())
	{
		m_indexState = 0;
	}
}

/**
 * @brief Anuleaz? rota?ia blocului, revenind la starea de rota?ie anterioar?.
 */
void Block::UndoRotate()
{
	m_indexState--;
	if (m_indexState < 0)
	{
		m_indexState = m_rotation.size() - 1;
	}
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip I.
 */
void Block::IBlock()
{
	m_rotation =
	{
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) },
		{ Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) },
		{ Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) },
		{ Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip L.
 */
void Block::LBlock()
{
	m_rotation =
	{
		{ Position(0, 2), Position(1, 0), Position(1, 1), Position(1, 2) },
		{ Position(0, 1), Position(1, 1), Position(2, 1), Position(2, 2) },
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 0) },
		{ Position(0, 0), Position(0, 1), Position(1, 1), Position(2, 1) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip J.
 */
void Block::JBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) },
		{ Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) },
		{ Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip Z.
 */
void Block::ZBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) },
		{ Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) },
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip S.
 */
void Block::SBlock()
{
	m_rotation =
	{
		{ Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) },
		{ Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) },
		{ Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) },
		{ Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip T.
 */
void Block::TBlock()
{
	m_rotation =
	{
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) },
		{ Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) }
	};
}

/**
 * @brief Configureaz? rota?iile posibile pentru un bloc de tip O.
 */
void Block::OBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) }
	};
}
