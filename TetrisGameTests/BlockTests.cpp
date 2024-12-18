#include <gtest/gtest.h>
#include "Block.h"

using namespace TetrisAPI;

namespace BlockTests
{
	TEST(BlockTest, Constructor)
	{
		Color color{ 0, 0, 0, 0 };
		Block block{ color, I };

		ASSERT_EQ(block.GetColor(), color);
		ASSERT_EQ(block.GetBlockType(), I);
	}

	TEST(BlockTest, RotatingBlockFourTimesGetsItToInitial)
	{
		Color color{ 0, 0, 0, 0 };
		Block block{ color, I };
		auto state{ block.GetCurrentRotation() };

		for (size_t i = 0; i < 4; i++)
			block.Rotate();
		auto stateAfterUndo{ block.GetCurrentRotation() };

		EXPECT_EQ(state, stateAfterUndo);
	}

	TEST(BlockTest, RotateUndoRotateWorks)
	{
		Color color{ 0, 0, 0, 0 };
		Block block{ color, I };
		auto state{ block.GetCurrentRotation() };

		block.Rotate();
		block.UndoRotate();
		auto stateAfterRotate{ block.GetCurrentRotation() };

		EXPECT_EQ(state, stateAfterRotate);
	}

	TEST(BlockTest, RotateDoesNothingToOBlock)
	{
		Color color{ 0, 0, 0, 0 };
		Block block{ color, O };
		auto state{ block.GetCurrentRotation() };

		block.Rotate();
		auto stateAfterRotate{ block.GetCurrentRotation() };

		EXPECT_EQ(state, stateAfterRotate);
	}
}