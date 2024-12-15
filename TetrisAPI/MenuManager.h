#pragma once
#include "../vcpkg_installed/x64-windows/x64-windows/include/raylib.h"
#include "GameModeStrategies.h"
#include <memory>

using namespace TetrisAPI;

class MenuManager
{
public:
    MenuManager();
    ~MenuManager();

    std::shared_ptr<IGameModeStrategy> ShowMenu();

private:
    void ShowTitleScreen();
    std::shared_ptr<IGameModeStrategy> ShowDifficultySelection();

    Font m_font;
};
