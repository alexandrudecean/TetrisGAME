#pragma once
#include <gmock/gmock.h>
#include "IInputManager.h"

using namespace TetrisAPI;
class IInputManagerMock : public IInputManager
{
public:
	MOCK_METHOD(bool, Check, (EInputType inputType), (override));
	MOCK_METHOD(void, Register, (EInputType inputType, uint16_t key), (override));
};