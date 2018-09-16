#include "Controller.h"

// Engine includes
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/Util/CameraManager.h"

// Game code includes
#include "Ticker.h"
#include "../GameComponents/LogicComponent.h"
#include "../GameComponents/DualLogicComponent.h"
#include "../GameComponents/RhythmLogicComponent.h"
#include "../GameComponents/ScreenShakeComponent.h"

#include <iostream>

Controller::Controller(Ticker * ticker, eGameMode mode)
	: m_state(eGameMode::rhythm)
	, m_pressed(false)
	, m_logic(nullptr)
	, ticker(ticker)
	, m_barsElapsed(0)
	, lastTick(0.f)
{
	// Initialize the logic based on the gamemode
	setLogicComponent(mode);
	// Save the camera center first
	center_x = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize().x / 2.f;
	center_y = GameEngine::GameEngineMain::GetInstance()->GetRenderWindow()->getSize().y / 2.f;
}

Controller::~Controller() {
	std::cout << "REMOVE!" << std::endl;
}

void Controller::Update() {
	// Update components
	Entity::Update();

	// Look for key inputs
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || 
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)  ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
	{
		// Only look for the moment the space bar is pressed
		if (!m_pressed) {
			m_pressed = true;
			// Call the handler function of the logic component
			m_logic->SpacePressed();
		}
	}
	else {
		// Reset the pressed flag once the space bar is no longer pressed
		m_pressed = false;
	}

	// Used for debug purposes.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
		swapState();
	}

	// If we exceed the number of bars until a switch, switch the game state
	// std::cout << "LAST: " << lastTick << ", CUR: " << ticker->getCurrentBarTick() << '\n';
	if (lastTick > ticker->getCurrentBarTick()) {
		m_barsElapsed++;
		if (m_barsElapsed >= NUM_BARS_UNTIL_SWITCH) {
			m_barsElapsed = 0;
			swapState();
		}
	}
	lastTick = ticker->getCurrentBarTick();
}

void Controller::OnAddToWorld() {
	Entity::OnAddToWorld();
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

	// Add a screen shake component
	m_shake = static_cast<ScreenShakeComponent*>(AddComponent<ScreenShakeComponent>());
	m_shake->setCenter(center_x, center_y);
	m_shake->setTime(1.f);

	// Add notes data to the new logic component
	m_logic->recieveData(notes);
}
