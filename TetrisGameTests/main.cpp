#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "Game.h"

using namespace testing;
using namespace TetrisAPI;

class IColorManagerMock : public IColorManager
{
public:
	MOCK_METHOD(Color, GetEmptyCellColor, (), (const override));
	MOCK_METHOD(Color, GetRandomBlockColor, (), (const override));
};

class IInputManagerMock : public IInputManager
{
public:
	MOCK_METHOD(bool, Check, (EInputType inputType), (override));
	MOCK_METHOD(void, Register, (EInputType inputType, uint16_t key), (override));
};

class IObserverMock : public IObserver
{
public:
	MOCK_METHOD(void, OnLinesCleared, (uint16_t linesCleared), (override));
};

namespace GameTests
{
	TEST(GameTest, Constructor)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color color(0, 0, 0, 0);

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillOnce(Return(color));

		Game game(colorManagerMock, inputManagerMock);
	}

	TEST(GameTest, FirstUpdateGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color color(0, 0, 0, 0);

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.Times(2)
			.WillRepeatedly(Return(color));

		Game game(colorManagerMock, inputManagerMock);
		game.Update();
	}
}

namespace TimerTests
{
	TEST(TimerTest, Constructor)
	{
		Timer timer(1);

		ASSERT_EQ(timer.IsActive(), false);
	}

	TEST(TimerTest, StartStopWorks)
	{
		Timer timer(1);
		timer.Start();
		
		ASSERT_EQ(timer.IsActive(), true);
		timer.Stop();
		ASSERT_EQ(timer.IsActive(), false);
	}

	TEST(TimerTest, GetElapsedTimeWorks)
	{
		Timer timer(3);
		timer.Start();

		std::this_thread::sleep_for(2s);
		
		ASSERT_EQ(timer.GetElapsedTime().count(), 2);
		ASSERT_EQ(timer.IsActive(), true);
	}

	TEST(TimerTest, ReachedThreshold)
	{
		Timer timer(3);
		timer.Start();

		std::this_thread::sleep_for(3s);
		
		ASSERT_EQ(timer.ReachedThreshold(), true);
	}
}

namespace ObservableTests
{
	TEST(ObservableTest, Register)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::shared_ptr<IObserverMock> observerMock = std::make_shared<IObserverMock>();
		
		EXPECT_CALL(*observerMock, OnLinesCleared(linesCleared))
			.Times(1);

		observable.Register(observerMock);

		observable.NotifyAll(linesCleared);
	}

	TEST(ObservableTest, Remove)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::shared_ptr<IObserverMock> observerMock = std::make_shared<IObserverMock>();

		EXPECT_CALL(*observerMock, OnLinesCleared(linesCleared))
			.Times(0);

		observable.Register(observerMock);
		observable.Remove(observerMock);

		observable.NotifyAll(linesCleared);
	}

	TEST(ObservableTest, NotifyAllGetsCalledForAllObservers)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::shared_ptr<IObserverMock> observerMock1 = std::make_shared<IObserverMock>();
		std::shared_ptr<IObserverMock> observerMock2 = std::make_shared<IObserverMock>();

		EXPECT_CALL(*observerMock1, OnLinesCleared(linesCleared));
		EXPECT_CALL(*observerMock2, OnLinesCleared(linesCleared));

		observable.Register(observerMock1);
		observable.Register(observerMock2);

		observable.NotifyAll(linesCleared);
	}

	TEST(ObservableTest, NotifyAllOnlyGetsCalledForAlivePointers)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::weak_ptr<IObserverMock> observerMockWeak;
		{
			std::shared_ptr<IObserverMock> observerMock = std::make_shared<IObserverMock>();
			observerMockWeak = observerMock;
			
			EXPECT_CALL(*observerMock, OnLinesCleared(linesCleared))
				.Times(0);
		}

		observable.Register(observerMockWeak);

		observable.NotifyAll(linesCleared);
	}
}

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

	TEST(GridTest, CheckConstructor) 
	{
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
