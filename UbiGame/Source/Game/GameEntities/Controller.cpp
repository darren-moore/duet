#include "Controller.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/ParticleComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "../GameComponents/LogicComponent.h"
#include "../GameComponents/DualLogicComponent.h"
#include "../GameComponents/RhythmLogicComponent.h"

#include <iostream>

Controller::Controller(eGameMode mode) {
	switch (mode) {
	case eGameMode::rhythm: {
		m_logic = static_cast<LogicComponent*>(AddComponent<RhythmLogicComponent>());
	} break;
	case eGameMode::dual: {
		m_logic = static_cast<LogicComponent*>(AddComponent<DualLogicComponent>());
	} break;
	default: {
		// Technically never supposed to happen
	} break;
	}
}

Controller::~Controller() {

}

void Controller::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		// Only look for the moment the space bar is pressed
		if (!m_pressed) {
			m_pressed = true;
			m_logic->SpacePressed();
			// Add a beat tap particle
			generateParticle();
		}
	}
	else {
		// Reset the pressed flag once the space bar is no longer pressed
		m_pressed = false;
	}
}

void Controller::OnAddToWorld() {

}

void Controller::OnRemoveFromWorld() {

}

void Controller::generateParticle() {
	GameEngine::Entity* bgEntity = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(bgEntity->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::TapParticle);
	render->SetZLevel(20);
	bgEntity->SetPos(sf::Vector2f(640.f, 360.f));
	bgEntity->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::ParticleComponent* part = static_cast<GameEngine::ParticleComponent*>(bgEntity->AddComponent<GameEngine::ParticleComponent>());
	part->SetLifeTime(0.1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(bgEntity);
}
