#include <gtest/gtest.h>
#include "IColorManagerMock.h"
#include "IInputManagerMock.h"
#include "IObserverMock.h"
#include <Game.h>
#include "IGameModeStrategyMock.h"

using namespace testing;

namespace GameTests
{
	TEST(GameTest, Constructor)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
		Color color{ 0, 0, 0, 0 };

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillOnce(Return(color));

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };
	}

	TEST(GameTest, FirstUpdateGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
		Color color{ 0, 0, 0, 0 };

		EXPECT_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillOnce(Return(color));
		EXPECT_CALL(*colorManagerMock, GetRandomBlockColor())
			.Times(2)
			.WillRepeatedly(Return(color));

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };
		game.Update();
	}

	TEST(GameTest, OnMoveDownNoOtherInputWillBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));

		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveDown))
			.Times(1)
			.WillOnce(Return(true));

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };

		game.Update();
	}

	TEST(GameTest, IfNotMoveDown_RotateAndMoveLeftRightInputWillBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(_))
			.WillByDefault(Return(false));

		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveDown));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveLeft));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveRight));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::Rotate));

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };

		game.Update();
	}

	TEST(GameTest, IfCheckMoveLeftTrueRightWillNotBeChecked)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
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
					case EInputType::MoveLeft: return true;
					default: return false;
					}
				});

		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveDown));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::Rotate));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveLeft));
		EXPECT_CALL(*inputManagerMock, Check(EInputType::MoveRight))
			.Times(0);

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };

		game.Update();
	}

	TEST(GameTest, OnRotateNotifyRotateGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
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
					case EInputType::Rotate: return true;
					default: return false;
					}
				});

		EXPECT_CALL(*observerMock, OnRotate);

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };
		game.Register(observerMock);

		game.Update();
	}

	TEST(GameTest, OnGameOverNotifyGameOverGetsCalled)
	{
		auto inputManagerMock = std::make_shared<IInputManagerMock>();
		auto colorManagerMock = std::make_shared<IColorManagerMock>();
		auto gameModeStrategyMock = std::make_shared<IGameModeStrategyMock>();
		auto observerMock = std::make_shared<IObserverMock>();

		Color emptyCellColor{ 0, 0, 0, 0 };
		Color blockColor{ 1, 1, 1, 1 };

		ON_CALL(*colorManagerMock, GetEmptyCellColor())
			.WillByDefault(Return(emptyCellColor));
		ON_CALL(*colorManagerMock, GetRandomBlockColor())
			.WillByDefault(Return(blockColor));
		ON_CALL(*inputManagerMock, Check(EInputType::MoveDown))
			.WillByDefault(Return(true));

		EXPECT_CALL(*observerMock, OnGameOver);

		Game game{ colorManagerMock, inputManagerMock, gameModeStrategyMock };
		game.Register(observerMock);

		while (!game.IsGameOver())
			game.Update();
	}
}
