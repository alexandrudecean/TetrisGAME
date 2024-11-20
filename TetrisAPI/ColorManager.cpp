#include "ColorManager.h"
#include <random>

using namespace TetrisAPI;

const Color ColorManager::Green{ 47, 230, 23, 255 };
const Color ColorManager::Red{ 232, 18, 18, 255 };
const Color ColorManager::Orange{ 226, 116, 17, 255 };
const Color ColorManager::Yellow{ 237, 234, 4, 255 };
const Color ColorManager::Purple{ 166, 0, 247, 255 };
const Color ColorManager::Cyan{ 21, 204, 209, 255 };
const Color ColorManager::Blue{ 13, 64, 216, 255 };
const Color ColorManager::LightBlue{ 59, 85, 162, 255 };
const Color ColorManager::DarkBlue{ 44, 44, 127, 255 };


ColorManager::ColorManager() :
    m_colors{ Green, Red, Orange, Yellow, Purple, Cyan, Blue, LightBlue, DarkBlue }
{}

Color ColorManager::GetRandomBlockColor() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, m_colors.size() - 1);
    uint16_t randomIndex = dist(gen);

    return m_colors[randomIndex];
}

Color ColorManager::GetEmptyCellColor() const
{
    return { 26, 31, 40, 255 };
}
