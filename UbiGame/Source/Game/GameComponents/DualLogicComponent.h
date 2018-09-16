/*
Contains gameplay logic for "dual" game mode.
*/

#pragma once
#include "LogicComponent.h"

class GameEngine::Entity;

class DualLogicComponent : public LogicComponent {

public:
	DualLogicComponent();
	~DualLogicComponent();

	void SpacePressed() override;

	void Update() override;
	void OnAddToWorld() override;

	std::vector<Note*> extractData() override;
	void recieveData(std::vector<Note*> notes) override;

private:
	std::vector<GameEngine::Entity*> m_noteEntities;
	float notesPos = 0;

	GameEngine::Entity * overlay;
};
