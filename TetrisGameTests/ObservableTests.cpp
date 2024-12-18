#include <gtest/gtest.h>
#include "Observable.h"
#include "IObserverMock.h"


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