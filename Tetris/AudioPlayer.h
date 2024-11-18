#pragma once
#include <raylib.h>
#include "IObserver.h"



class AudioPlayer :public TetrisAPI::IObserver
{
public:
	AudioPlayer();
	void OnLinesCleared(uint16_t numLines);
	void OnRotate();
	void OnGameOver();

	inline Music GetMusic() const { return m_music; }

	~AudioPlayer();

private:
	Music m_music;
	Sound m_rotateSound;
	Sound m_clearedSound;
	Sound m_gameOverSound;
};

