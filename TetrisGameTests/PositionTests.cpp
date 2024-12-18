#include <gtest/gtest.h>
#include "Position.h"

using namespace TetrisAPI;

namespace PositionTests
{
	TEST(PositionTest, CheckConstructor)
	{
		Position position{ 0,1 };

		ASSERT_EQ(position.GetX(), 0);
		ASSERT_EQ(position.GetY(), 1);
	}

	TEST(PositionTest, CheckEqualsOperator)
	{
		Position position1{ 0,1 };
		Position position2{ 0,1 };

		ASSERT_EQ(position1, position2);
	}

	TEST(PositionTest, CheckPlusOperator)
	{
		Position position1{ 0,1 };
		Position position2{ 2,3 };

		Position result = position1 + position2;

		ASSERT_EQ(position1, Position(0, 1));
		ASSERT_EQ(position2, Position(2, 3));
		ASSERT_EQ(result, Position(2, 4));
	}

	TEST(PositionTest, CheckPlusEqualsOperator)
	{
		Position position1{ 0,1 };
		Position position2{ 2,3 };

		position1 += position2;

		ASSERT_EQ(position1, Position(2, 4));
		ASSERT_EQ(position2, Position(2, 3));
	}
}