#pragma once
#include <stdint.h>


namespace TetrisAPI
{
	class IObserver
	{
	public:
		virtual void OnLinesCleared(uint16_t numLines) = 0;
	};
}