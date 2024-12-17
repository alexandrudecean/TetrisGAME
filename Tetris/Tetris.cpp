/**
 * @file main.cpp
 * @brief Implementarea principală a jocului Tetris, incluzând meniul, gestionarea input-urilor și logica de joc.
 *
 * Acest fișier conține funcțiile necesare pentru inițializarea jocului, interacțiunea utilizatorului și afișarea
 * conținutului grafic. Este punctul de intrare al aplicației Tetris.
 *
 */

#include <iostream>
#include "DrawManager.h"
#include "InputManager.h"
#include "ColorManager.h"
#include "AudioPlayer.h"
#include <GameModeStrategies.h>

/**
 * @brief Creeaza și returnează un obiect InputManager configurat cu mapările de taste.
 *
 * @return IInputManagerPtr Pointer inteligent către un obiect InputManager configurat.
 */


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


/**
 * @brief Creează și returnează un obiect ColorManager.
 *
 * @return IColorManagerPtr Pointer inteligent către un obiect ColorManager.
 */

IColorManagerPtr GetColorManager()
{
	using namespace TetrisAPI;
	ColorManager colorManager;
	return std::make_shared<ColorManager>(colorManager);
}
/**
 * @brief Creează și returnează un obiect Game.
 *
 * @param inputManager Pointer inteligent către un obiect InputManager.
 * @param gameModeStrategy Pointer inteligent către strategia de mod de joc selectată.
 * @return IGamePtr Pointer inteligent către un obiect Game.
 */

IGamePtr GetGame(const IInputManagerPtr& inputManager, IGameModeStrategyPtr gameModeStrategy)
{
	using namespace TetrisAPI;
	Game game{ std::move(GetColorManager()), inputManager, std::move(gameModeStrategy) };
	return std::make_unique<Game>(game);
}

/**
 * @brief Inițializează observatorii jocului, cum ar fi AudioPlayer și ScoreManager.
 *
 * @param audioPlayer Referință la un pointer inteligent către AudioPlayer.
 * @param scoreManager Referință la un pointer inteligent către ScoreManager.
 */

void InitObservers(AudioPlayerPtr& audioPlayer, ScoreManagerPtr& scoreManager)
{
	using namespace TetrisAPI;
	audioPlayer = std::make_shared<AudioPlayer>();
	scoreManager = std::make_shared<ScoreManager>();
}

/**
 * @brief Înregistrează observatorii pentru un obiect Game.
 *
 * @param game Pointer inteligent către un obiect Game.
 * @param observers Vector de pointeri către observatori.
 */
void RegisterObservers(IGamePtr& game, const std::vector<IObserverPtr>& observers)
{
	std::ranges::for_each(observers, [&game](const IObserverPtr& observer)
		{
			game->Register(observer);
		});
}

/**
 * @brief Resetează starea tastelor apăsate.
 */
void ResetInputState()
{
	while (GetKeyPressed() != 0);
}

/**
 * @brief Afișează meniul principal al jocului și permite utilizatorului să selecteze modul de joc.
 *
 * @return IGameModeStrategyPtr Pointer inteligent către strategia de mod de joc selectată sau nullptr dacă fereastra este închisă.
 */
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


/**
 * @brief Afișează jocul principal, gestionând logica și redarea grafică.
 *
 * @param gameModeStrategy Pointer inteligent către strategia de mod de joc selectată.
 */
void ShowGame(const IGameModeStrategyPtr& gameModeStrategy)
{
	Font font = GetFontDefault();
	const int screenWidth = 800;
	const int screenHeight = 910;

	if (IsWindowReady())
	{
		CloseWindow();
	}

	InitWindow(screenWidth, screenHeight, "Tetris Game");
	InitAudioDevice();
	SetTargetFPS(60);

	auto inputManager = GetInputManager();
	IGamePtr game = GetGame(inputManager, gameModeStrategy);

	AudioPlayerPtr audioPlayer;
	ScoreManagerPtr scoreManager;

	InitObservers(audioPlayer, scoreManager);
	RegisterObservers(game, { audioPlayer, scoreManager });

	while (!WindowShouldClose())
	{
		UpdateMusicStream(audioPlayer->GetMusic());
		game->Update();

		if (game->IsGameOver())
		{
			if (inputManager->Check(TetrisAPI::EInputType::Reset))
			{
				game = GetGame(inputManager, gameModeStrategy);
				InitObservers(audioPlayer, scoreManager);
				RegisterObservers(game, { audioPlayer, scoreManager });
			}

			if (IsKeyPressed(KEY_SPACE))
			{
				ResetInputState(); 
				break;
			}
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


/**
 * @brief Punctul de intrare al aplicației. Afișează meniul și lansează jocul pe baza selecției utilizatorului.
 *
 * @return int Codul de ieșire al aplicației.
 */
int main()
{
	while (true) 
	{
		auto gameModeStrategy = ShowMenu(); 

		if (gameModeStrategy) 
		{
			ShowGame(gameModeStrategy); 
		}
		else
		{
			break; 
		}
	}

	return 0;
}