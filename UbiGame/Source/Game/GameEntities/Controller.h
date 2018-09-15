#pragma once

#include "GameEngine/EntitySystem/Entity.h"
#include "../Util/Common.h"

class LogicComponent;

class Controller : public GameEngine::Entity {

public:
	Controller(eGameMode mode = eGameMode::rhythm);
	~Controller();

	void Update() override;

	void OnAddToWorld() override;
	void OnRemoveFromWorld() override;
private:
	bool m_pressed;
	LogicComponent * m_logic;

	void generateParticle();
};