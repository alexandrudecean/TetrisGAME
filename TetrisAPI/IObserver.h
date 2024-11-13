#pragma once


namespace TetrisAPI
{
	class IObserver
	{
	public:
		virtual void OnLinesCleared(int numLines) = 0;
	};
}