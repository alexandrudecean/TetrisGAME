#pragma once
#include <raylib.h>
#include <memory>
#include "BaseObserver.h"

class AudioPlayer;
using AudioPlayerPtr = std::shared_ptr<AudioPlayer>;

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
	Music m_music;
	Sound m_rotateSound;
	Sound m_clearedSound;
	Sound m_gameOverSound;
};

