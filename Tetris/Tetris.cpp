#include <iostream>
#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "AudioPlayer.h"


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

IGamePtr GetGame(const IInputManagerPtr& inputManager)
{
	using namespace TetrisAPI;
	Game game{ std::move(GetColorManager()), inputManager };
	return std::make_unique<Game>(game);
}

void InitObservers(AudioPlayerPtr& audioPlayer, ScoreManagerPtr& scoreManager)
{
	using namespace TetrisAPI;
	//audioPlayer = std::make_shared<AudioPlayer>();
	scoreManager = std::make_shared<ScoreManager>();
}

void RegisterObservers(IGamePtr& game, const std::vector<IObserverPtr>& observers)
{
	std::ranges::for_each(observers, [&game](const IObserverPtr& observer) 
		{
			game->Register(observer);
		});
}

void ShowGame()
{
	Font font = GetFontDefault();

	const int screenWidth = 800;
	const int screenHeight = 910;

	InitWindow(screenWidth, screenHeight, "Tetris Game");
	InitAudioDevice();
	SetTargetFPS(60);

	auto inputManager = GetInputManager();
	
	IGamePtr game(std::move(GetGame(inputManager)));

	AudioPlayerPtr audioPlayer;
	ScoreManagerPtr scoreManager;
	
	InitObservers(audioPlayer, scoreManager);
	//RegisterObservers(game, { audioPlayer, scoreManager });
	RegisterObservers(game, { scoreManager });

	while (WindowShouldClose() == false)
	{
		//UpdateMusicStream(audioPlayer->GetMusic());
		game->Update();
		if (game->IsGameOver() && inputManager->Check(TetrisAPI::Reset))
		{
			game = std::move(GetGame(inputManager));
			InitObservers(audioPlayer, scoreManager);
			//RegisterObservers(game, { audioPlayer, scoreManager });
			RegisterObservers(game, { scoreManager });
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawGrid(game->GetGrid());
		DrawScore(font, scoreManager);
		DrawNextBlock(font, game);
		DrawGameOver(font, game);

		EndDrawing();
	}

	CloseAudioDevice();
	CloseWindow();
}


int main()
{
	ShowGame();
	return 0;
}