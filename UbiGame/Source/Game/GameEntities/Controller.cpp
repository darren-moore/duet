#include "Controller.h"

#include "GameEngine/GameEngineMain.h"
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
