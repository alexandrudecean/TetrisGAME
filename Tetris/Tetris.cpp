#include "DrawManager.h"



void ShowGame()
{
    Color Dark_Green = { 20, 160, 133, 255 };

    const int screenWidth = 800;
    const int screenHeight = 1000;
    APIGrid grid(APIColor(26, 31, 40, 255));
    APIBlock block(APIColor(200,35,45,255),TetrisAPI::L);
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
    GetKeyPressed();
    return 0;
}