#include "ScoreManager.h"

using namespace TetrisAPI;

ScoreManager::ScoreManager():m_score(0)
{}


void ScoreManager::OnLinesCleared(uint16_t numLines)
{
    if (numLines == 1)
        m_score += 100;
    else if (numLines == 2)
        m_score += 300;
    else if (numLines == 3)
        m_score += 500;
    else
        m_score += 1000;
}
