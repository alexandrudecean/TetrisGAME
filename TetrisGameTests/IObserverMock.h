#pragma once
#include <gmock/gmock.h>
#include "IObserver.h"

using namespace TetrisAPI;

class IObserverMock : public IObserver
{
public:
	MOCK_METHOD(void, OnLinesCleared, (uint16_t linesCleared), (override));
	MOCK_METHOD(void, OnRotate, (), (override));
	MOCK_METHOD(void, OnGameOver, (), (override));
	MOCK_METHOD(void, OnMoveDown, (), (override));
};