#include "MenuManager.h"

MenuManager::MenuManager()
{
    InitWindow(800, 600, "Tetris Menu");
    m_font = GetFontDefault();
}

MenuManager::~MenuManager()
{
    CloseWindow();
}

std::shared_ptr<IGameModeStrategy> MenuManager::ShowMenu()
{
    ShowTitleScreen();
    return ShowDifficultySelection();
}

void MenuManager::ShowTitleScreen()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextEx(m_font, "TETRIS", { 250, 200 }, 80, 2, WHITE);

        // Start button
        Rectangle startButton = { 300, 350, 200, 60 };
        DrawRectangleRec(startButton, LIGHTGRAY);
        DrawText("START", 340, 365, 30, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), startButton))
        {
            return;
        }

        EndDrawing();
    }
}

std::shared_ptr<IGameModeStrategy> MenuManager::ShowDifficultySelection()
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Select Difficulty:", 240, 200, 40, WHITE);

		// Easy button
        Rectangle easyButton = { 200, 300, 200, 60 };
        DrawRectangleRec(easyButton, GREEN);
        DrawText("EASY", 250, 315, 30, BLACK);

		// Hard button
        Rectangle hardButton = { 400, 300, 200, 60 };
        DrawRectangleRec(hardButton, RED);
        DrawText("HARD", 450, 315, 30, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            if (CheckCollisionPointRec(mousePos, easyButton))
            {
                return std::make_shared<EasyModeStrategy>();
            }
            if (CheckCollisionPointRec(mousePos, hardButton))
            {
                return std::make_shared<HardModeStrategy>();
            }
        }

        EndDrawing();
    }
    return nullptr;
}
