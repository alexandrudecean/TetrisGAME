#pragma once
#include <stdint.h>

namespace TetrisAPI
{
	class ScoreManager
	{
	public:
		ScoreManager(uint16_t score);
		uint16_t GetScore();

	private:
		uint16_t m_score;
	};
}


