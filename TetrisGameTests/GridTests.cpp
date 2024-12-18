#include <gtest/gtest.h>
#include "Grid.h"
#include "Color.h"

using namespace TetrisAPI;

namespace GridTests
{
	std::vector<std::vector<Color>> CreateEmptyGridMatrix(const Color& emptyCellColor)
	{
		std::vector<std::vector<Color>> gridMatrix;
		for (size_t i = 0; i < Grid::HEIGHT; i++)
		{
			std::vector<Color> line;
			for (size_t j = 0; j < Grid::WIDTH; j++)
			{
				line.emplace_back(emptyCellColor);
			}
			gridMatrix.emplace_back(line);
		}
		return gridMatrix;
	}

	TEST(GridTest, CheckConstructor)
	{
		Color emptyCellColor{ 0, 0, 0, 0 };
		auto expectedGridMatrix{ CreateEmptyGridMatrix(emptyCellColor) };

		Grid grid{ emptyCellColor };

		const auto& actualGridMatrix = grid.GetGrid();

		ASSERT_EQ(grid.BlockCanMove(), false);
		ASSERT_EQ(expectedGridMatrix.size(), actualGridMatrix.size());
		for (size_t i = 0; i < actualGridMatrix.size(); i++)
		{
			EXPECT_EQ(expectedGridMatrix[i], actualGridMatrix[i]);
		}
	}
}