/*
Contains gameplay logic for "dual" game mode.
*/

#pragma once
#include "LogicComponent.h"

class DualLogicComponent : public LogicComponent {

public:
	DualLogicComponent();
	~DualLogicComponent();

	void SpacePressed() override;

	void Update() override;
	void OnAddToWorld() override;

};