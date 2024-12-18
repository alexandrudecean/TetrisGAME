/**
 * @file AudioPlayer.h
 * @brief Declarația clasei AudioPlayer pentru gestionarea sunetelor din jocul Tetris.
 *
 * Clasa AudioPlayer este un observator care răspunde la evenimentele jocului, cum ar fi ștergerea liniilor,
 * rotația blocurilor și sfârșitul jocului, prin redarea de sunete corespunzătoare.
 */

#pragma once
#include <raylib.h>
#include <memory>
#include "BaseObserver.h"


class AudioPlayer;

/**
 * @typedef AudioPlayerPtr
 * @brief Tip definit pentru un pointer inteligent către un obiect AudioPlayer.
 */
using AudioPlayerPtr = std::shared_ptr<AudioPlayer>;

/**
 * @class AudioPlayer
 * @brief Clasa pentru gestionarea efectelor sonore și muzicii din joc.
 *
 * AudioPlayer moștenește funcționalitățile clasei BaseObserver și implementează răspunsurile
 * la evenimentele jocului. Gestionarea sunetelor include muzica de fundal, sunetul la rotație,
 * sunetul pentru ștergerea liniilor și sunetul pentru sfârșitul jocului.
 */
class AudioPlayer :public TetrisAPI::BaseObserver
{
public:
	AudioPlayer();
	void OnLinesCleared(uint16_t numLines);
	void OnRotate();
	void OnGameOver();

	inline Music GetMusic() const { return m_music; }

	~AudioPlayer();
private:
	Music m_music;          ///< Muzica de fundal a jocului.
	Sound m_rotateSound;    ///< Sunetul redat la rotația unui bloc.
	Sound m_clearedSound;   ///< Sunetul redat la ștergerea liniilor.
	Sound m_gameOverSound;  ///< Sunetul redat la sfârșitul jocului.
};

