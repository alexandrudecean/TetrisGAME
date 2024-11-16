#pragma once
#include <iostream>


namespace TetrisAPI
{
	class IObserver
	{
	public:
		virtual void OnLinesCleared(uint16_t numLines) = 0;
	};
}