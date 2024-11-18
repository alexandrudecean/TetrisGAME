#pragma once
#include <stdint.h>
#include "IObserver.h"

namespace TetrisAPI
{
	class ScoreManager : public IObserver
	{
	public:
		ScoreManager();
		uint16_t GetScore() const;
		void OnLinesCleared(uint16_t numLines);
		inline void OnRotate() { return; }
		inline void OnGameOver() { return; }

	private:
		uint16_t m_score;
	};
}


