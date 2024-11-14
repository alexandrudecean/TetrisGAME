#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Grid.h"

using testing::Return;
using namespace TetrisAPI;

class ColorManagerMock : public IColorManager
{
public:
	MOCK_METHOD(Color, GetEmptyCellColor, (), (const override));
	MOCK_METHOD(Color, GetRandomBlockColor, (), (const override));
};

namespace GridTests 
{
	std::vector<std::vector<Color>> CreateEmptyGridMatrix(Color emptyCellColor)
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

	TEST(GridTest, CheckConstructor) {
		Color emptyCellColor(0, 0, 0, 0);
		auto expectedMatrixGrid = CreateEmptyGridMatrix(emptyCellColor);

		Grid grid(emptyCellColor);

		auto actualGridMatrix = grid.GetGrid();

		ASSERT_EQ(grid.BlockCanMove(), false);
		ASSERT_EQ(expectedMatrixGrid.size(), actualGridMatrix.size());
		for (size_t i = 0; i < actualGridMatrix.size(); i++)
		{
			ASSERT_EQ(expectedMatrixGrid[i].size(), actualGridMatrix[i].size());

			for (size_t j = 0; j < actualGridMatrix[i].size(); j++)
			{
				ASSERT_EQ(expectedMatrixGrid[i][j], actualGridMatrix[i][j]);
			}
		}
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
