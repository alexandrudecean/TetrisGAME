#pragma once
#include "IObserver.h"

namespace TetrisAPI
{
	class BaseObserver : public IObserver
	{
		inline virtual void OnLinesCleared(uint16_t numLines) override { return; }
		inline virtual void OnRotate() override { return; }
		inline virtual void OnGameOver() override { return; }
		inline virtual void OnMoveDown() override { return; }
	};

}
