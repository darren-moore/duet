/*
The base class for different gameplay states.
*/

#pragma once
#include "GameEngine\EntitySystem\Component.h"

class Ticker;

class LogicComponent : public GameEngine::Component {

public:
	LogicComponent();
	~LogicComponent();

	inline void setTicker(Ticker* ticker) { this->ticker = ticker; }

	virtual void SpacePressed();

	virtual void Update();
	virtual void OnAddToWorld();

protected:
	// A reference to a ticker
	Ticker * ticker;
};