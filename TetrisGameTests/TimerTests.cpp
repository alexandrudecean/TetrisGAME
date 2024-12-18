#include <gtest/gtest.h>
#include "Timer.h"
#include <thread>

using namespace TetrisAPI;

namespace TimerTests
{
	TEST(TimerTest, Constructor)
	{
		Timer timer{ 1 };

		ASSERT_EQ(timer.IsActive(), false);
	}

	TEST(TimerTest, StartStopWorks)
	{
		Timer timer{ 1 };
		timer.Start();

		ASSERT_EQ(timer.IsActive(), true);
		timer.Stop();
		ASSERT_EQ(timer.IsActive(), false);
	}

	TEST(TimerTest, GetElapsedTimeWorks)
	{
		Timer timer{ 3000 };
		timer.Start();

		std::this_thread::sleep_for(2s);

		auto elapsedTime = timer.GetElapsedTime().count();
		ASSERT_GE(elapsedTime, 2000);
		ASSERT_LE(elapsedTime, 2100);
		ASSERT_EQ(timer.IsActive(), true);
	}

	TEST(TimerTest, ReachedThreshold)
	{
		Timer timer{ 3 };
		timer.Start();

		std::this_thread::sleep_for(3s);

		ASSERT_EQ(timer.ReachedThreshold(), true);
	}
}