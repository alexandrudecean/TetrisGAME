#pragma once

namespace TetrisAPI
{
	class ScoreManager
	{
	public:
		ScoreManager(int score);
		int GetScore();

	private:
		int m_score;
	};
}


