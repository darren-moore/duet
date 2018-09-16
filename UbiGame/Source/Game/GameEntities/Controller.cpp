#include "Controller.h"

// Engine includes
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/ParticleComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

// Game code includes
#include "Ticker.h"
#include "../GameComponents/LogicComponent.h"
#include "../GameComponents/DualLogicComponent.h"
#include "../GameComponents/RhythmLogicComponent.h"

#include <iostream>

Controller::Controller(Ticker * ticker, eGameMode mode)
	: m_state(eGameMode::rhythm)
	, m_pressed(false)
	, m_logic(nullptr)
	, ticker(ticker)
	, m_beatsElapsed(0)
	, lastTick(0.f)
{
	// Initialize the logic based on the gamemode
	setLogicComponent(mode);
}

Controller::~Controller() {

}

void Controller::Update() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		// Only look for the moment the space bar is pressed
		if (!m_pressed) {
			m_pressed = true;
			// Call the handler function of the logic component
			m_logic->SpacePressed();
			// Add a beat tap particle
			generateParticle();
		}
	}
	else {
		// Reset the pressed flag once the space bar is no longer pressed
		m_pressed = false;
	}

	// Update the logic component
	m_logic->Update();

	// If we exceed the number of bars until a switch, switch the game state
	if (lastTick > ticker->getCurrentBarTick()) {
		m_beatsElapsed++;
		if (m_beatsElapsed >= NUM_BARS_UNTIL_SWITCH) {
			m_beatsElapsed = 0;
			swapState();
		}
	}
	lastTick = ticker->getCurrentBarTick();
}

void Controller::OnAddToWorld() {

}

void Controller::OnRemoveFromWorld() {

}

void Controller::setLogicComponent(eGameMode mode) {
	switch (mode) {
	case eGameMode::rhythm: {
		m_logic = static_cast<LogicComponent*>(AddComponent<RhythmLogicComponent>());
		m_logic->setTicker(ticker);
		m_state = eGameMode::rhythm;
	} break;
	case eGameMode::dual: {
		m_logic = static_cast<LogicComponent*>(AddComponent<DualLogicComponent>());
		m_logic->setTicker(ticker);
		m_state = eGameMode::dual;
	} break;
	default: {
		// Technically never supposed to happen
	} break;
	}
}

void Controller::generateParticle() {
	GameEngine::Entity* fill = new GameEngine::Entity();
	// Setup the sprite for the fill
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(fill->AddComponent<GameEngine::SpriteRenderComponent>());
	render->SetTexture(GameEngine::eTexture::TapParticle);
	render->SetZLevel(20);
	fill->SetPos(sf::Vector2f(640.f, 360.f));
	fill->SetSize(sf::Vector2f(1280.f, 720.f));
	// Set the lifetime for the fill to dissapear after 100 milliseconds
	GameEngine::ParticleComponent* part = static_cast<GameEngine::ParticleComponent*>(fill->AddComponent<GameEngine::ParticleComponent>());
	part->SetLifeTime(0.1f);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(fill);
}

void Controller::swapState() {
	// Save the level data first
	std::vector<Note*> notes = m_logic->extractData();
	// Then re-instantiate the components based on the state
	DestroyComponents();
	switch (m_state) {
	case eGameMode::rhythm: {
		setLogicComponent(eGameMode::dual);
		m_state = eGameMode::dual;
	} break;
	case eGameMode::dual: {
		setLogicComponent(eGameMode::rhythm);
		m_state = eGameMode::rhythm;
	} break;
	default: {
		// Technically never supposed to happen
	} break;
	}
	// Add notes data to the new logic component
	m_logic->recieveData(notes);
}
