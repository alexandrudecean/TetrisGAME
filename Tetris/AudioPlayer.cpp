/**
 * @file AudioPlayer.cpp
 * @brief Implementarea clasei AudioPlayer pentru gestionarea efectelor sonore și muzicii din joc.
 *
 * Această clasă gestionează redarea muzicii de fundal și a efectelor sonore pentru evenimentele
 * specifice din joc, cum ar fi rotirea blocurilor, ștergerea liniilor și sfârșitul jocului.
 */
#include "AudioPlayer.h"

 /**
  * @brief Constructorul clasei AudioPlayer.
  *
  * Încarcă muzica de fundal și efectele sonore necesare pentru joc și începe redarea muzicii.
  */
AudioPlayer::AudioPlayer()
{
	m_music = LoadMusicStream("../Sounds/playSound.mp3");
	SetMusicVolume(m_music, 0.1f);
	PlayMusicStream(m_music);
	m_clearedSound = LoadSound("../Sounds/clear.mp3");
	m_rotateSound = LoadSound("../Sounds/rotate.mp3");
	m_gameOverSound = LoadSound("../Sounds/gameOver.mp3");
}


/**
 * @brief Reacționează la evenimentul de ștergere a liniilor din grilă.
 *
 * @param numLines Numărul de linii șterse (nefolosit în această implementare).
 */
void AudioPlayer::OnLinesCleared(uint16_t numLines)
{
	PlaySound(m_clearedSound);
}

/**
 * @brief Reacționează la evenimentul de rotire a unui bloc.
 */
void AudioPlayer::OnRotate()
{
	PlaySound(m_rotateSound);
}

/**
 * @brief Reacționează la evenimentul de Game Over.
 *
 * Oprește muzica de fundal și redă sunetul specific pentru Game Over.
 */
void AudioPlayer::OnGameOver()
{
	StopMusicStream(m_music);
	PlaySound(m_gameOverSound);
}

/**
 * @brief Destructorul clasei AudioPlayer.
 *
 * Eliberează memoria utilizată pentru sunete și muzică.
 */
AudioPlayer::~AudioPlayer()
{
	UnloadSound(m_clearedSound);
	UnloadSound(m_rotateSound);
	UnloadSound(m_gameOverSound);
	UnloadMusicStream(m_music);
}
