#pragma once
#include <gmock/gmock.h>
#include "IGameModeStrategy.h"

using namespace TetrisAPI;

class IGameModeStrategyMock : public IGameModeStrategy
{
public:
    MOCK_METHOD(uint16_t, GetMoveDownInterval, (), (const, override));
    MOCK_METHOD(bool, ShowNextBlocks, (), (const, override));
};