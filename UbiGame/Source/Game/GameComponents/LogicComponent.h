/*
The base class for different gameplay states.
*/

#pragma once
#include "GameEngine\EntitySystem\Component.h"

#include <vector>

class Ticker;
struct Note;

class LogicComponent : public GameEngine::Component {

public:
	LogicComponent();
	~LogicComponent();

	inline void setTicker(Ticker* ticker) { this->ticker = ticker; }

	virtual void SpacePressed();

	virtual void Update();
	virtual void OnAddToWorld();

	// Just recieve the data as a vector of notes
	virtual std::vector<Note*> extractData();
	virtual void recieveData(std::vector<Note*> notes);

protected:
	// A reference to a ticker
	Ticker * ticker;
};