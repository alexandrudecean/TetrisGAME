#include "ScoreManager.h"

using namespace TetrisAPI;

ScoreManager::ScoreManager(uint16_t score):m_score(score)
{
}

uint16_t ScoreManager::GetScore()
{
    return m_score;
}
