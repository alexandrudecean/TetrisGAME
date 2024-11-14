#include "Block.h"

using namespace TetrisAPI;

Block::Block(const Color& color, EBlockType blockType) :m_color(color), m_blockType(blockType)
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

void Block::Rotate()
{
	indexState++;
	if (indexState == (int)m_rotation.size())
	{
		indexState = 0;
	}
}

void Block::UndoRotate()
{
	indexState--;
	if (indexState < 0)
	{
		indexState = (int)m_rotation.size() - 1;
	}
}

std::vector<Position> Block::GetCurrentRotation() const
{
	return m_rotation[indexState];
}

Color Block::GetColor() const
{
	return m_color;
}

void TetrisAPI::Block::IBlock()
{
	m_rotation =
	{
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(1, 3) },
		{ Position(0, 2), Position(1, 2), Position(2, 2), Position(3, 2) },
		{ Position(2, 0), Position(2, 1), Position(2, 2), Position(2, 3) },
		{ Position(0, 1), Position(1, 1), Position(2, 1), Position(3, 1) }
	};
}

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

void TetrisAPI::Block::JBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(1, 0), Position(1, 1), Position(1, 2) },
		{ Position(0, 1), Position(0, 2), Position(1, 1), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 2) },
		{ Position(0, 1), Position(1, 1), Position(2, 0), Position(2, 1) }
	};
}

void TetrisAPI::Block::ZBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(0, 1), Position(1, 1), Position(1, 2) },
		{ Position(0, 2), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(2, 1), Position(2, 2) },
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 0) }
	};
}

void TetrisAPI::Block::SBlock()
{
	m_rotation =
	{
		{ Position(0, 1), Position(0, 2), Position(1, 0), Position(1, 1) },
		{ Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 2) },
		{ Position(1, 1), Position(1, 2), Position(2, 0), Position(2, 1) },
		{ Position(0, 0), Position(1, 0), Position(1, 1), Position(2, 1) }
	};
}

void TetrisAPI::Block::TBlock()
{
	m_rotation =
	{
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(1, 2) },
		{ Position(0, 1), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(1, 0), Position(1, 1), Position(1, 2), Position(2, 1) },
		{ Position(0, 1), Position(1, 0), Position(1, 1), Position(2, 1) }
	};
}

void TetrisAPI::Block::OBlock()
{
	m_rotation =
	{
		{ Position(0, 0), Position(0, 1), Position(1, 0), Position(1, 1) }
	};
}
