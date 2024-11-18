#include <iostream>
#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "Game.h"
#include "ScoreManager.h"

using IGamePtr = std::unique_ptr<TetrisAPI::IGame>;

IInputManagerPtr GetInputManager()
{
	using namespace TetrisAPI;
	InputManager inputManager;
	inputManager.Register(MoveDown, KEY_DOWN);
	inputManager.Register(MoveLeft, KEY_LEFT);
	inputManager.Register(MoveRight, KEY_RIGHT);
	inputManager.Register(Rotate, KEY_UP);
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

void DrawScore(const Font& font, const TetrisAPI::ScoreManager& scoreManager)
{
	std::string scoreText = std::to_string(scoreManager.GetScore());
	DrawTextEx(font, "Score:", { 540,45 }, 48, 2, WHITE);
	DrawRectangleRounded({ 520,100,200,80 }, 0.3, 6, LIGHTGRAY);
	DrawTextEx(font, scoreText.c_str(), { 525,120 }, 48, 2, BLACK);
}

void DrawNextBlock(const Font& font, const IGamePtr& game)
{
	DrawTextEx(font, "Next:", { 540,245 }, 48, 2, WHITE);
	DrawRectangleRounded({ 520,300,200,220 }, 0.3, 6, LIGHTGRAY);

	switch (game->GetNextBlock().GetBlockType())
	{
	case TetrisAPI::EBlockType::I:
		DrawBlock(game->GetNextBlock(), 555, 320);
		break;
	case TetrisAPI::EBlockType::O:
		DrawBlock(game->GetNextBlock(), 570, 350);
		break;
	default:
		DrawBlock(game->GetNextBlock(), 570, 320);
		break;
	}
}

void DrawGameOver(const Font& font, const IGamePtr& game)
{
	if (game->IsGameOver())
	{
		DrawTextEx(font, "GAME OVER", { 480,645 }, 48, 2, WHITE);
	}
}

void ShowGame()
{
	Font font = GetFontDefault();

	const int screenWidth = 800;
	const int screenHeight = 910;

	InitWindow(screenWidth, screenHeight, "Tetris Game");
	SetTargetFPS(60);

	IGamePtr game(std::move(GetGame()));
	auto scoreManger = std::make_shared<TetrisAPI::ScoreManager>();
	game->Register(scoreManger);

	while (WindowShouldClose() == false)
	{
		game->Update();

		BeginDrawing();
		ClearBackground(BLACK);

		DrawGrid(game->GetGrid());
		DrawScore(font, *scoreManger);
		DrawNextBlock(font, game);
		DrawGameOver(font, game);

		EndDrawing();
	}

	CloseWindow();
}


int main()
{
	ShowGame();
	return 0;
}