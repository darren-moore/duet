#pragma once

#include "LogicComponent.h"

#include <vector>

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
};