﻿#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
	m_music = LoadMusicStream("../Sounds/playSound.mp3");
	SetMusicVolume(m_music, 0.1f);
	PlayMusicStream(m_music);
	m_clearedSound = LoadSound("../Sounds/clear.mp3");
	m_rotateSound = LoadSound("../Sounds/rotate.mp3");
	m_gameOverSound = LoadSound("../Sounds/gameOver.mp3");
}

void AudioPlayer::OnLinesCleared(uint16_t numLines)
{
	PlaySound(m_clearedSound);
}

void AudioPlayer::OnRotate()
{
	PlaySound(m_rotateSound);
}

void AudioPlayer::OnGameOver()
{
	StopMusicStream(m_music);
	PlaySound(m_gameOverSound);
}

AudioPlayer::~AudioPlayer()
{
	UnloadSound(m_clearedSound);
	UnloadSound(m_rotateSound);
	UnloadSound(m_gameOverSound);
	UnloadMusicStream(m_music);
}
