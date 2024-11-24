#pragma once
#include <memory>
#include <vector>
#include "IObserver.h"

using IObserverPtr = std::weak_ptr<TetrisAPI::IObserver>;

namespace TetrisAPI 
{
	class Observable
	{
	public:
		void Register(const IObserverPtr& observer);
		void Remove(const IObserverPtr& observer);
		void NotifyLinesCleared(uint16_t numLines);
		void NotifyGameOver();
		void NotifyRotateBlock();
		void NotifyMoveDownBlock();
	private:
		std::vector<IObserverPtr> m_observers;
	};
}

