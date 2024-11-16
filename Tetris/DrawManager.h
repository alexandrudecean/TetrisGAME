#include <raylib.h>
#include "Grid.h"

using APIColor = TetrisAPI::Color;
using APIGrid = TetrisAPI::Grid;
using APIBlock = TetrisAPI::Block;

static const uint16_t CELL_SIZE = 45;
static const uint16_t CELL_BORDER = 2;


Color GetRaylibColor(const APIColor& color);
void DrawGrid(const APIGrid& grid);
void DrawBlock(const APIBlock& block, uint16_t offsetX, uint16_t offsetY);


