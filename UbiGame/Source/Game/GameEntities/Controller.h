/*
Handles player input before dispatching to logic components.
*/

#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "../Util/Common.h"

#define NUM_BARS_UNTIL_SWITCH 4.f

class LogicComponent;
class Ticker;

class Controller : public GameEngine::Entity {

public:
	Controller(Ticker * ticker, eGameMode mode = eGameMode::rhythm);
	~Controller();

	inline LogicComponent * getLogicComponent() const { return m_logic; }

	void Update() override;

	void OnAddToWorld() override;
	void OnRemoveFromWorld() override;
private:
	// Keep track of the current game state within the controller
	// This is probably bad design but I don't have the energy to think of anything else
	eGameMode m_state;
	
	bool m_pressed;
	LogicComponent * m_logic;

	// Keep a reference to the ticker to handle state transitioning at the right time
	Ticker * ticker;
	int m_beatsElapsed;
	float lastTick;

	void setLogicComponent(eGameMode mode);
	void swapState();
};