#include "ColorManager.h"
#include <ctime>
#include <cstdlib>

using namespace TetrisAPI;

Color ColorManager::GetRandomBlockColor() const
{
    std::srand(std::time(nullptr));
    uint16_t randomIndex = std::rand() % m_colors.size();

    return m_colors[randomIndex];
}

Color ColorManager::GetEmptyCellColor() const
{
    return Color(26, 31, 40, 255);
}
