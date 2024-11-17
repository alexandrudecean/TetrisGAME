#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "Game.h"

using IGamePtr = std::unique_ptr<TetrisAPI::IGame>;

IInputManagerPtr GetInputManager()
{
    using namespace TetrisAPI;
    InputManager inputManager;
    inputManager.Register(MoveDown, KEY_SPACE);
    inputManager.Register(MoveLeft, KEY_A);
    inputManager.Register(MoveRight, KEY_D);
    inputManager.Register(Rotate, KEY_R);
    return std::make_shared<InputManager>(inputManager);
}

IColorManagerPtr GetColorManager()
{
    using namespace TetrisAPI;
    ColorManager colorManager;
    return std::make_shared<ColorManager>(colorManager);
}

IGamePtr GetGame()
{
    using namespace TetrisAPI;
    Game game(std::move(GetColorManager()), std::move(GetInputManager()));
    return std::make_unique<Game>(game);
}

void ShowGame()
{
    Color Dark_Green = { 20, 160, 133, 255 };

    const int screenWidth = 800;
    const int screenHeight = 1000;
    
    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);
    
    IGamePtr game(std::move(GetGame()));

    while (WindowShouldClose() == false) {
        game->Update();
        
        BeginDrawing();
        ClearBackground(Dark_Green);
        
        
        DrawGrid(game->GetGrid());
        //DrawBlock(game->GetNextBlock(), 0, 0);
        
        EndDrawing();
    }

    CloseWindow();
}


int main() 
{
    
    ShowGame();
    return 0;
}