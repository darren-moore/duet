#pragma once

#include "LogicComponent.h"

class RhythmLogicComponent : public LogicComponent {

public:
	RhythmLogicComponent();
	~RhythmLogicComponent();

	void SpacePressed() override;

	void Update() override;
	void OnAddToWorld() override;
private:
	
};