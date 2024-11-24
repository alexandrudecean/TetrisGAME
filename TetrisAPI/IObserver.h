#pragma once
#include <stdint.h>


namespace TetrisAPI
{
	class IObserver
	{
	public:
		virtual void OnLinesCleared(uint16_t numLines) = 0;
		virtual void OnRotate() = 0;
		virtual void OnGameOver() = 0;
		virtual void OnMoveDown() = 0;
	};
}