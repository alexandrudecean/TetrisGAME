#include "Block.h"

using namespace TetrisAPI;

Block::Block(const Color& color, EBlockType blockType):m_color(color),m_blockType(blockType)
{
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
		indexState = (int)m_rotation.size()-1;
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
