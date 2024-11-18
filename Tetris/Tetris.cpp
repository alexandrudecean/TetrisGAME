#include <iostream>
#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "Game.h"
#include "AudioPlayer.h"


IInputManagerPtr GetInputManager()
{
	using namespace TetrisAPI;
	InputManager inputManager;
	inputManager.Register(MoveDown, KEY_DOWN);
	inputManager.Register(MoveLeft, KEY_LEFT);
	inputManager.Register(MoveRight, KEY_RIGHT);
	inputManager.Register(Rotate, KEY_UP);
	inputManager.Register(Reset, KEY_ENTER);
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
	Font font = GetFontDefault();
	auto inputManager = GetInputManager();

	const int screenWidth = 800;
	const int screenHeight = 910;

	InitWindow(screenWidth, screenHeight, "Tetris Game");
	SetTargetFPS(60);

	IGamePtr game(std::move(GetGame()));
	auto audioPlayer = std::make_shared<AudioPlayer>();
	auto scoreManger = std::make_shared<TetrisAPI::ScoreManager>();
	game->Register(scoreManger);
	game->Register(audioPlayer);

	while (WindowShouldClose() == false)
	{
		UpdateMusicStream(audioPlayer->GetMusic());
		game->Update();
		if (game->IsGameOver() && inputManager->Check(TetrisAPI::Reset))
		{
			game = std::move(GetGame());
			scoreManger= std::make_shared<TetrisAPI::ScoreManager>();
			game->Register(scoreManger);
		}

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