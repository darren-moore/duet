#pragma once

#include "GameEngine\EntitySystem\Component.h"

class LogicComponent : public GameEngine::Component {

public:
	LogicComponent();
	~LogicComponent();

	virtual void SpacePressed();

	virtual void Update();
	virtual void OnAddToWorld();
};