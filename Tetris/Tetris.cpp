#include "DrawManager.h"
#include "InputManager.h"
#include "Game.h"
#include "ColorManager.h"


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

void ShowGame()
{
    Color Dark_Green = { 20, 160, 133, 255 };

    const int screenWidth = 800;
    const int screenHeight = 1000;
    APIGrid grid(APIColor(26, 31, 40, 255));
    TetrisAPI::ColorManager colorManager;
    APIColor color = colorManager.GetRandomBlockColor();
    APIBlock block(color,TetrisAPI::GetRandomBlockType()); 
    //grid.SpawnBlock(TetrisAPI::Block(APIColor(200, 32, 48, 255), TetrisAPI::EBlockType::I));
    InitWindow(screenWidth, screenHeight, "Tetris Game");
    SetTargetFPS(60);

    while (WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(Dark_Green);
        DrawGrid(grid);
        DrawBlock(block,0, 0);
        EndDrawing();
    }

    CloseWindow();
}


int main() 
{
    
    ShowGame();
    return 0;
}