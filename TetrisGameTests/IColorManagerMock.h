#pragma once
#include <gmock/gmock.h>
#include "IColorManager.h"

using namespace TetrisAPI;

class IColorManagerMock : public IColorManager
{
public:
	MOCK_METHOD(Color, GetEmptyCellColor, (), (const override));
	MOCK_METHOD(Color, GetRandomBlockColor, (), (const override));
};