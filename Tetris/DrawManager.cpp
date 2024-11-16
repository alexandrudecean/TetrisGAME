#include "DrawManager.h"


Color GetRaylibColor(const APIColor& color)
{
	return { color.GetR(),color.GetG(), color.GetB(),color.GetA() };
}


void DrawGrid(const APIGrid& grid)
{
	auto matrixGrid = grid.GetGrid();
	for (size_t row = 0; row < APIGrid::HEIGHT;row++)
	{
		for (size_t column = 0; column < APIGrid::WIDTH; column++)
		{
			Color color = GetRaylibColor(matrixGrid[row][column]);
			DrawRectangle(column * CELL_SIZE + CELL_BORDER, row * CELL_SIZE + CELL_BORDER, CELL_SIZE - CELL_BORDER, CELL_SIZE - CELL_BORDER, color);
		}
	}
}

void DrawBlock(const APIBlock& block, uint16_t offsetX, uint16_t offsetY)
{
	auto squares = block.GetCurrentRotation();
	for (const auto& square : squares)
	{
		Color color = GetRaylibColor(block.GetColor());
		DrawRectangle(square.GetX() * CELL_SIZE + offsetX+ CELL_BORDER, square.GetY() * CELL_SIZE + offsetY+ CELL_BORDER, CELL_SIZE - CELL_BORDER, CELL_SIZE - CELL_BORDER,color );
	}
}

