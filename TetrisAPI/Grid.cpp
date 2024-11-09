#include "Grid.h"

Grid::Grid(IColorManager* colorManager) :
	m_emptyCellColor(colorManager->GetEmptyCellColor())
{
	for (size_t i = 0; i < HEIGHT; i++)
	{
		std::vector<Color> line;
		for (size_t j = 0; j < WIDTH; j++)
		{
			line.emplace_back(m_emptyCellColor);
		}
		m_grid.emplace_back(line);
	}
}

void Grid::SpawnBlock(const Block& block)
{
	m_currentBlock = block;
	m_currentBlockOffset = Position::Origin;

	for (const auto& pos : m_currentBlock.GetCurrentRotation())
	{
		(*this)[pos + m_currentBlockOffset] = m_currentBlock.GetColor();
	}
}

void Grid::MoveDownCurrentBlock()
{
	m_currentBlockOffset += Position(0, 1);
}

bool Grid::IsPositionEmpty(Position& pos) const
{
	return (*this)[pos] == m_emptyCellColor;
}

Color& Grid::operator[](const Position& pos)
{
	return m_grid[pos.GetY()][pos.GetX()];
}

const Color& Grid::operator[](const Position& pos) const
{
	return m_grid[pos.GetY()][pos.GetX()];
}
