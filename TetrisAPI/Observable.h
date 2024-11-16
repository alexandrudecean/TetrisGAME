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
		void NotifyAll(uint16_t numLines);
	private:
		std::vector<std::weak_ptr<IObserver>> m_observers;
	};
}

