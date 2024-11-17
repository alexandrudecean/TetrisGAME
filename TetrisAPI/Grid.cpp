#include "Grid.h"

using namespace TetrisAPI;

Grid::Grid(const Color& emptyCellColor) :
	m_emptyCellColor(emptyCellColor),
	m_blockCanMove(false)
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

void Grid::MoveDown()
{
	while (m_blockCanMove)
		Move(Position::Down);
}

uint16_t Grid::ClearFullLines()
{
	uint16_t linesCleared = 0;
	int16_t fullLine = GetFullLine();
	while (fullLine != -1)
	{
		linesCleared++;
		ClearLine(fullLine);
		fullLine = GetFullLine();
	}
	return linesCleared;
}

void Grid::Rotate()
{
	if (!m_blockCanMove)
		return;

	RemoveCurrentBlock();
	m_currentBlock->Rotate();
	if (TrySpawnCurrentBlock(m_currentBlockOffset) == Succes)
		SpawnCurrentBlock();
	else
		m_currentBlock->UndoRotate();
}

void Grid::Move(const Position& pos)
{
	Position newOffset = m_currentBlockOffset + pos;
	RemoveCurrentBlock();
	EResult result = TrySpawnCurrentBlock(newOffset);
	if (result == Succes)
	{
		m_currentBlockOffset = newOffset;
		SpawnCurrentBlock();
		return;
	}

	if (pos == Position::Down)
		m_blockCanMove = false;
	
	SpawnCurrentBlock();
}

bool Grid::BlockCanMove() const
{
	return m_blockCanMove;
}

std::vector<std::vector<Color>> TetrisAPI::Grid::GetGrid() const
{
	return m_grid;
}

void Grid::SpawnBlock(const Block& block)
{
	m_currentBlock = block;
	m_currentBlockOffset = Position::Origin;
	m_blockCanMove = true;

	SpawnCurrentBlock();
}

int16_t Grid::GetFullLine() const
{
	for (int16_t lineIndex = HEIGHT - 1; lineIndex >= 0; lineIndex--)
	{
		if (LineIsFull(lineIndex))
			return lineIndex;
	}
	return -1;
}

bool Grid::LineIsFull(size_t line) const
{
	for (size_t i = 0; i < WIDTH; i++)
	{
		if (IsPositionEmpty(Position(i, line)))
			return false;
	}
	return true;
}

void Grid::ClearLine(size_t line)
{
	for (size_t i = line; i > 0; i--)
	{
		for (size_t j = 0; j < WIDTH; j++)
		{
			m_grid[i][j] = m_grid[i - 1][j];
		}
	}
	for (size_t j = 0; j < WIDTH; j++)
	{
		m_grid[0][j] = m_emptyCellColor;
	}
}

EResult Grid::TrySpawnCurrentBlock(const Position& offset) const
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		Position position = pos + offset;
		EResult result = TrySpawnAt(position);
		if (result != Succes)
			return result;
	}
	return Succes;
}

EResult Grid::TrySpawnAt(const Position& pos) const
{
	if (IsPositionInGrid(pos))
	{
		if (IsPositionEmpty(pos))
			return Succes;
		return Collision;
	}
	return OutOfBounds;
}

void Grid::SetCurrentBlockCells(const Color& color)
{
	for (const auto& pos : m_currentBlock->GetCurrentRotation())
	{
		(*this)[pos + m_currentBlockOffset] = color;
	}
}

void Grid::SpawnCurrentBlock()
{
	SetCurrentBlockCells(m_currentBlock->GetColor());
}

void Grid::RemoveCurrentBlock()
{
	SetCurrentBlockCells(m_emptyCellColor);
}

bool Grid::IsPositionEmpty(const Position& pos) const
{
	return (*this)[pos] == m_emptyCellColor;
}

bool Grid::IsPositionInGrid(const Position& pos) const
{
	return  pos.GetX() >= 0 && pos.GetX() < WIDTH &&
		pos.GetY() >= 0 && pos.GetY() < HEIGHT;
}

Color& Grid::operator[](const Position& pos)
{
	return m_grid[pos.GetY()][pos.GetX()];
}

const Color& Grid::operator[](const Position& pos) const
{
	return m_grid[pos.GetY()][pos.GetX()];
}
