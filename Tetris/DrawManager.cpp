#include "DrawManager.h"


Color GetRaylibColor(const APIColor& color)
{
	return { color.GetR(),color.GetG(), color.GetB(),color.GetA() };
}


void DrawGrid(const APIGrid& grid)
{
	const auto& matrixGrid = grid.GetGrid();
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
	const auto& squares = block.GetCurrentRotation();
	for (const auto& square : squares)
	{
		Color color = GetRaylibColor(block.GetColor());
		DrawRectangle(square.GetX() * CELL_SIZE + offsetX+ CELL_BORDER, square.GetY() * CELL_SIZE + offsetY+ CELL_BORDER, CELL_SIZE - CELL_BORDER, CELL_SIZE - CELL_BORDER,color );
	}
}


void DrawScore(const Font& font, const ScoreManagerPtr& scoreManager)
{
	std::string scoreText{ std::to_string(scoreManager->GetScore()) };
	DrawTextEx(font, "Score:", { 540, 45 }, 48, 2, WHITE);
	DrawRectangleRounded({ 520, 100, 200, 80 }, 0.3, 6, LIGHTGRAY);
	DrawTextEx(font, scoreText.c_str(), { 525, 120 }, 48, 2, BLACK);
}

void DrawNextBlock(const Font& font, const IGamePtr& game)
{
	DrawTextEx(font, "Next:", { 540, 545 }, 48, 2, WHITE);
	DrawRectangleRounded({ 520, 600, 200, 220 }, 0.3, 6, LIGHTGRAY);

	switch (game->GetNextBlock().GetBlockType())
	{
	case TetrisAPI::EBlockType::I:
		DrawBlock(game->GetNextBlock(), 555, 620);
		break;
	case TetrisAPI::EBlockType::O:
		DrawBlock(game->GetNextBlock(), 570, 650);
		break;
	default:
		DrawBlock(game->GetNextBlock(), 570, 620);
		break;
	}
}

//salut

void DrawGameOver(const Font& font, const IGamePtr& game)
{
	if (game->IsGameOver())
	{
		Color color = { 200, 200, 200, 128 };
		DrawRectangleRounded({ 0, 0, 800, 910 }, 0, 6, color);
		DrawTextEx(font, "GAME OVER", { 120, 245 }, 108, 2, BLACK);
		DrawTextEx(font, "For reset, press:", { 60, 385 }, 88, 2,BLACK);
		DrawTextEx(font, "ENTER", { 170, 520 }, 130, 2,BLACK);
	}
}

void DrawnGooLuck(const Font& font, const IGamePtr& game)
{
	DrawTextEx(font, "Good Luck :D", { 490, 350 }, 48, 2, WHITE);
}
