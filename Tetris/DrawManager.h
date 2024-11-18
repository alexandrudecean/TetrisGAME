#include <raylib.h>
#include "Game.h"
#include "ScoreManager.h"

using IGamePtr = std::unique_ptr<TetrisAPI::IGame>;

using APIColor = TetrisAPI::Color;
using APIGrid = TetrisAPI::Grid;
using APIBlock = TetrisAPI::Block;

static const uint16_t CELL_SIZE = 45;
static const uint16_t CELL_BORDER = 5;


Color GetRaylibColor(const APIColor& color);
void DrawGrid(const APIGrid& grid);
void DrawBlock(const APIBlock& block, uint16_t offsetX, uint16_t offsetY);
void DrawScore(const Font& font, const TetrisAPI::ScoreManager& scoreManager);
void DrawNextBlock(const Font& font, const IGamePtr& game);
void DrawGameOver(const Font& font, const IGamePtr& game);




