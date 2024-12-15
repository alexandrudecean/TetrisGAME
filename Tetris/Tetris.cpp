#include <iostream>
#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "AudioPlayer.h"
#include <GameModeStrategies.h>


IInputManagerPtr GetInputManager()
{
	using namespace TetrisAPI;
	InputManager inputManager;
	inputManager.Register(MoveDown, KEY_DOWN);
	inputManager.Register(MoveDown, KEY_S);
	inputManager.Register(MoveLeft, KEY_LEFT);
	inputManager.Register(MoveLeft, KEY_A);
	inputManager.Register(MoveRight, KEY_RIGHT);
	inputManager.Register(MoveRight, KEY_D);
	inputManager.Register(Rotate, KEY_UP);
	inputManager.Register(Rotate, KEY_R);
	inputManager.Register(Reset, KEY_ENTER);
	return std::make_shared<InputManager>(inputManager);
}

IColorManagerPtr GetColorManager()
{
	using namespace TetrisAPI;
	ColorManager colorManager;
	return std::make_shared<ColorManager>(colorManager);
}

IGamePtr GetGame(const IInputManagerPtr& inputManager, IGameModeStrategyPtr gameModeStrategy)
{
	using namespace TetrisAPI;
	Game game{ std::move(GetColorManager()), inputManager, std::move(gameModeStrategy) };
	return std::make_unique<Game>(game);
}

void InitObservers(AudioPlayerPtr& audioPlayer, ScoreManagerPtr& scoreManager)
{
	using namespace TetrisAPI;
	audioPlayer = std::make_shared<AudioPlayer>();
	scoreManager = std::make_shared<ScoreManager>();
}

void RegisterObservers(IGamePtr& game, const std::vector<IObserverPtr>& observers)
{
	std::ranges::for_each(observers, [&game](const IObserverPtr& observer)
		{
			game->Register(observer);
		});
}

IGameModeStrategyPtr ShowMenu()
{
	using namespace TetrisAPI;
	Font font = GetFontDefault();
	InitWindow(800, 600, "Tetris Menu");
	SetTargetFPS(60);

	IGameModeStrategyPtr selectedStrategy = nullptr;

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(::BLACK);

		DrawTextEx(font, "TETRIS", { 250, 150 }, 80, 2, ::WHITE);

		Rectangle easyButton = { 300, 300, 200, 60 };
		DrawRectangleRec(easyButton, ::GREEN);
		DrawText("EASY", 355, 315, 30, ::BLACK);

		Rectangle hardButton = { 300, 400, 200, 60 };
		DrawRectangleRec(hardButton, ::RED);
		DrawText("HARD", 350, 415, 30, ::BLACK);

		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			Vector2 mousePos = GetMousePosition();

			if (CheckCollisionPointRec(mousePos, easyButton))
			{
				selectedStrategy = std::make_shared<EasyModeStrategy>();
				break;
			}
			if (CheckCollisionPointRec(mousePos, hardButton))
			{
				selectedStrategy = std::make_shared<HardModeStrategy>();
				break;
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return selectedStrategy;
}

void ShowGame(const IGameModeStrategyPtr& gameModeStrategy)
{
	Font font = GetFontDefault();
	const int screenWidth = 800;
	const int screenHeight = 910;

	InitWindow(screenWidth, screenHeight, "Tetris Game");
	InitAudioDevice();
	SetTargetFPS(60);

	auto inputManager = GetInputManager();
	IGamePtr game(std::move(GetGame(inputManager, gameModeStrategy)));

	AudioPlayerPtr audioPlayer;
	ScoreManagerPtr scoreManager;

	InitObservers(audioPlayer, scoreManager);
	RegisterObservers(game, { audioPlayer, scoreManager });

	while (!WindowShouldClose())
	{
		UpdateMusicStream(audioPlayer->GetMusic());
		game->Update();
		if (game->IsGameOver() && inputManager->Check(TetrisAPI::EInputType::Reset))
		{
			game = GetGame(inputManager, gameModeStrategy);
			InitObservers(audioPlayer, scoreManager);
			RegisterObservers(game, { audioPlayer, scoreManager });
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawGoodLuckMessage(font, game);
		DrawGrid(game->GetGrid());
		DrawScore(font, scoreManager);

		if (game->ShowNextBlocks())
		{
			DrawNextBlock(font, game);
		}
		DrawGameOver(font, game);

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}

int main()
{
	auto gameModeStrategy = ShowMenu();

	if (gameModeStrategy) 
	{
		ShowGame(gameModeStrategy);
	}

	return 0;
}