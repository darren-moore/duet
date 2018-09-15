#include "Ticker.h"

#include "GameEngine/GameEngineMain.h"

#include <iostream>

Ticker::Ticker(int bpm)
	: m_bpm(bpm)
	, m_soundManager(new GameEngine::SoundManager(10))
	, timer(0.f)
	, step(60.f / static_cast<float>(bpm))
	, goal(0.f)
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
	goal = 0.f;
}

void Ticker::OnRemoveFromWorld() {

}

void Ticker::Update() {
	if (m_playing) {
		timer += GameEngine::GameEngineMain::GetTimeDelta();
		if (timer > goal) {
			std::cout << "GOAL!" << std::endl;
			goal += step;
		}
	}
	else {
		// Only start the ticking once the music is playing
		if (m_soundManager->GetCurrentMusicOffset() > 0) {
			m_playing = true;
		}
	}
}
