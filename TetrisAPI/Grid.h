#pragma once
#include "Block.h"
#include "IColorManager.h"

class Grid
{
public:
	Grid(IColorManager* colorManager);
private:
	void SpawnBlock(const Block& block);
	void MoveDownCurrentBlock();
	bool IsPositionEmpty(Position& pos) const;

	Color& operator[](const Position& pos);
	const Color& operator[](const Position& pos) const;
private:
	std::vector<std::vector<Color>> m_grid;
	Block m_currentBlock;
	Position m_currentBlockOffset;
	const Color m_emptyCellColor;

	static inline const int WIDTH = 15;
	static inline const int HEIGHT = 15;
};

