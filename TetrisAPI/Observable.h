#pragma once
#include "IObserver.h"

namespace TetrisAPI {

	class Observable
	{
	public:
		void Register(IObserver* observer);
		void Remove(IObserver* observer);
		void NotifyAll(uint16_t numLines);

	};
}

