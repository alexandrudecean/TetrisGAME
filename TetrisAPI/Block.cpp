#include "Block.h"

using namespace TetrisAPI;

void Block::Rotate()
{
}

void Block::UndoRotate()
{
}

std::vector<Position> Block::GetCurrentRotation() const
{
	return std::vector<Position>();
}

Color Block::GetColor() const
{
	return Color(0, 0, 0, 0);
}
