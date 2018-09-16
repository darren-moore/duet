/*
Handles player input before dispatching to logic components.
*/

#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "../Util/Common.h"

#define NUM_BARS_UNTIL_RHYTHM_SWITCH 12.f
#define NUM_BARS_UNTIL_DUAL_SWITCH 4.f

class LogicComponent;
class ScreenShakeComponent;
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
	
	bool m_leftPressed, m_rightPressed;
	LogicComponent * m_logic;
	ScreenShakeComponent * m_shake;

	// Keep a reference to the ticker to handle state transitioning at the right time
	Ticker * ticker;
	int m_barsElapsed;
	float lastTick;

	void setLogicComponent(eGameMode mode);
	void swapState();

	// Variables for controlling camera shake
	float center_x, center_y;
	float offset_x, offset_y;

	// Reference to the metrenome sprite entity
	GameEngine::Entity * m_metronome;
	void createMetronomeSpirit();
};