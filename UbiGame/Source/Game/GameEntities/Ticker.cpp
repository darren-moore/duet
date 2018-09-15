#include "Ticker.h"

#include "GameEngine/GameEngineMain.h"

#include <iostream>
#include <cmath>

Ticker::Ticker(int bpm)
	: m_bpm(bpm)
	, m_soundManager(new GameEngine::SoundManager(10))
	, timer(0.f)
	, step(60.f / static_cast<float>(bpm))
	, m_playing(false)
{
	
}

Ticker::~Ticker() {
	delete m_soundManager;
}

void Ticker::OnAddToWorld() {
	m_soundManager->PlayMusic("Resources/snd/track.wav");
	m_soundManager->setMusicLoop(true);
	timer = 0.f;
	step = 60.f / static_cast<float>(m_bpm);
}

void Ticker::OnRemoveFromWorld() {

}

void Ticker::Update() {
	if (m_playing) {
		timer += GameEngine::GameEngineMain::GetTimeDelta();
		if (timer > step * NUM_BEATS_IN_BAR) {
			timer = 0.f;
		}
	}
	else {
		// Only start the ticking once the music is playing
		if (m_soundManager->GetCurrentMusicOffset() > 0) {
			m_playing = true;
		}
	}
}

float Ticker::getCurrentBarTick() const {
	return timer;
}
