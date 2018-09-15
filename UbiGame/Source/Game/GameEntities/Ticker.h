#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/Util/SoundManager.h"

class Ticker : public GameEngine::Entity {

public:
	Ticker(int bpm = 120);
	~Ticker();

	void OnAddToWorld() override;
	void OnRemoveFromWorld() override;

	void Update() override;
private:
	int m_bpm;
	GameEngine::SoundManager * m_soundManager;
	float timer, step, goal;

	bool m_playing;
};