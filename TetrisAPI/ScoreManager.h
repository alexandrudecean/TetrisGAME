#pragma once
#include <stdint.h>
#include "BaseObserver.h"

namespace TetrisAPI
{
	class ScoreManager : public BaseObserver
	{
	public:
		ScoreManager();
		uint16_t GetScore() const;
		void OnLinesCleared(uint16_t numLines) override;
	private:
		uint16_t m_score;
	};
}


