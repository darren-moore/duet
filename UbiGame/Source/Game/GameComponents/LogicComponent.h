#pragma once

#include "GameEngine\EntitySystem\Component.h"

class LogicComponent : public GameEngine::Component {

protected:
	LogicComponent() {}
	~LogicComponent() {}

	virtual void Update();
	virtual void OnAddToWorld();
};