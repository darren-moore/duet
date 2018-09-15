#pragma once

#include "LogicComponent.h"

#include <vector>

class Ticker;

class RhythmLogicComponent : public LogicComponent {

public:
	RhythmLogicComponent();
	~RhythmLogicComponent();

	void SpacePressed() override;

	void Update() override;
	void OnAddToWorld() override;
private:
	// The 4 bars represented in the screen
	std::vector<float> bars[4];
	int current;
	int bpm;

	float DistanceToNearestNote(float beat);
};