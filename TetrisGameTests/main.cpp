#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <thread>

#include "Game.h"
#include "ScoreManager.h"

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
	MOCK_METHOD(void, OnRotate, (), (override));
	MOCK_METHOD(void, OnGameOver, (), (override));
};

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

namespace GameTests
{
	TEST(GameTest, Constructor)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color color{ 0, 0, 0, 0 };

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillOnce(Return(color));

		Game game{ colorManagerMock, inputManagerMock };
	}

	TEST(GameTest, FirstUpdateGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color color{ 0, 0, 0, 0 };

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.Times(2)
			.WillRepeatedly(Return(color));

		Game game{ colorManagerMock, inputManagerMock };
		game.Update();
	}

	TEST(GameTest, OnMoveDownNoOtherInputWillBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));

		EXPECT_CALL(*inputManagerMock, Check(MoveDown))
			.Times(1)
			.WillOnce(Return(true));

		Game game{ colorManagerMock, inputManagerMock };

		game.Update();
	}

	TEST(GameTest, IfNotMoveDown_RotateAndMoveLeftRightInputWillBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(_))
			.WillByDefault(Return(false));

		EXPECT_CALL(*inputManagerMock, Check(MoveDown));
		EXPECT_CALL(*inputManagerMock, Check(MoveLeft));
		EXPECT_CALL(*inputManagerMock, Check(MoveRight));
		EXPECT_CALL(*inputManagerMock, Check(Rotate));

		Game game{ colorManagerMock, inputManagerMock };

		game.Update();
	}

	TEST(GameTest, IfCheckMoveLeftTrueRightWillNotBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(_))
			.WillByDefault([](EInputType input)
				{
					switch (input)
					{
					case MoveLeft: return true;
					default: return false;
					}
				});

		EXPECT_CALL(*inputManagerMock, Check(MoveDown));
		EXPECT_CALL(*inputManagerMock, Check(Rotate));
		EXPECT_CALL(*inputManagerMock, Check(MoveLeft));
		EXPECT_CALL(*inputManagerMock, Check(MoveRight))
			.Times(0);

		Game game{ colorManagerMock, inputManagerMock };

		game.Update();
	}

	TEST(GameTest, OnRotateNotifyRotateGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto observerMock = std::make_shared<IObserverMock>();

		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(_))
			.WillByDefault([](EInputType input)
				{
					switch (input)
					{
					case Rotate: return true;
					default: return false;
					}
				});

		EXPECT_CALL(*observerMock, OnRotate);

		Game game{ colorManagerMock, inputManagerMock };
		game.Register(observerMock);

		game.Update();
	}

	TEST(GameTest, OnGameOverNotifyGameOverGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto observerMock = std::make_shared<IObserverMock>();

		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(MoveDown))
			.WillByDefault(Return(true));

		EXPECT_CALL(*observerMock, OnGameOver);

		Game game{ colorManagerMock, inputManagerMock };
		game.Register(observerMock);

		while (!game.IsGameOver())
			game.Update();
	}
}

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
		Timer timer{ 3 };
		timer.Start();

		std::this_thread::sleep_for(2s);

		ASSERT_EQ(timer.GetElapsedTime().count(), 2);
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

		observable.NotifyLinesCleared(linesCleared);
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

		observable.NotifyLinesCleared(linesCleared);
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

		observable.NotifyLinesCleared(linesCleared);
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

		observable.NotifyLinesCleared(linesCleared);
	}

	TEST(ObservableTest, NotifyGameOverWorks)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::shared_ptr<IObserverMock> observerMock = std::make_shared<IObserverMock>();

		EXPECT_CALL(*observerMock, OnGameOver());

		observable.Register(observerMock);

		observable.NotifyGameOver();
	}

	TEST(ObservableTest, NotifyRotateWorks)
	{
		Observable observable;
		uint16_t linesCleared = 2;
		std::shared_ptr<IObserverMock> observerMock = std::make_shared<IObserverMock>();

		EXPECT_CALL(*observerMock, OnRotate());

		observable.Register(observerMock);

		observable.NotifyRotateBlock();
	}
}

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

namespace ColorTests
{
	TEST(ColorTest, CheckConstructor)
	{
		uint8_t m_r = 0;
		uint8_t m_g = 25;
		uint8_t m_b = 30;
		uint8_t m_a = 255;

		Color color{ m_r,m_g,m_b,m_a };

		ASSERT_EQ(color.GetR(), m_r);
		ASSERT_EQ(color.GetG(), m_g);
		ASSERT_EQ(color.GetB(), m_b);
		ASSERT_EQ(color.GetA(), m_a);
	}

	TEST(ColorTest, CheckEqualsOperator)
	{
		uint8_t m_r = 0;
		uint8_t m_g = 25;
		uint8_t m_b = 30;
		uint8_t m_a = 255;

		Color color1{ m_r,m_g,m_b,m_a };
		Color color2{ m_r,m_g,m_b,m_a };

		ASSERT_EQ(color1, color2);
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
