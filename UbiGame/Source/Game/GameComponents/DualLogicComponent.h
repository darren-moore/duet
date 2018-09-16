/*
Contains gameplay logic for "dual" game mode.
*/

#pragma once
#include "LogicComponent.h"
#include <SFML/System/Vector2.hpp>
#include <queue>

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
	void processNoteEntitiy(GameEngine::Entity* note);
	// 0 1 2
	// 5 4 3
	std::vector<std::vector<Note*>> notes;
	std::vector<std::vector<GameEngine::Entity*>> entities;

	float lastTick;
	sf::Vector2f bottomSpawnPoint = sf::Vector2f(-640, 400);
	sf::Vector2f topSpawnPoint = sf::Vector2f(1280+640, 200);

	bool halfTimeFlag = false;
	int current = 0;
	int bpm = 120;
	int bars = 0;
	GameEngine::Entity * overlay;
};
