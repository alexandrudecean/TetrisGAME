#pragma once
#include <memory>
#include <vector>
#include "IObserver.h"

namespace TetrisAPI 
{
	class Observable
	{
	public:
		void Register(const std::weak_ptr<IObserver>& observer);
		void Remove(const std::weak_ptr<IObserver>& observer);
		void NotifyLinesCleared(uint16_t numLines);
		void NotifyGameOver();
		void NotifyRotateBlock();
	private:
		std::vector<std::weak_ptr<IObserver>> m_observers;
	};
}

