/*
Handles music playback and beat tracking.
*/

#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/Util/SoundManager.h"

#define NUM_BEATS_IN_BAR 4

class Ticker : public GameEngine::Entity {

public:
	Ticker(int bpm = 120);
	~Ticker();

	void OnAddToWorld() override;
	void OnRemoveFromWorld() override;

	void Update() override;

	float getCurrentBarTick() const;
private:
	int m_bpm;
	GameEngine::SoundManager * m_soundManager;
	float timer, step;

	bool m_playing;
};
