#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "../Util/Common.h"

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
	bool m_pressed;
	LogicComponent * m_logic;

	void generateParticle();
};