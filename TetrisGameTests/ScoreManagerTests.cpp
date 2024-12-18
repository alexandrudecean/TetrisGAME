#include <gtest/gtest.h>
#include "ScoreManager.h"

using namespace TetrisAPI;

namespace ScoreManagerTests
{
	TEST(ScoreManagerTest, Constructor)
	{
		ScoreManager scoreManager;

		ASSERT_EQ(scoreManager.GetScore(), 0);
	}

	TEST(ScoreManagerTest, OnLinesClearedWorks)
	{
		ScoreManager scoreManager;
		scoreManager.OnLinesCleared(3);

		ASSERT_TRUE(scoreManager.GetScore() != 0);
	}
}