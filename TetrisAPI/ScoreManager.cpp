#include "ScoreManager.h"

using namespace TetrisAPI;

ScoreManager::ScoreManager(int score):m_score(score)
{
}

int ScoreManager::GetScore()
{
    return m_score;
}
