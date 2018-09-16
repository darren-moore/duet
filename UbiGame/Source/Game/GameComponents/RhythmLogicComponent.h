/*
Contains gameplay logic for "rhythm" game mode.
*/

#pragma once
#include "LogicComponent.h"

#include <vector>

struct Note;
class GameEngine::Entity;

class RhythmLogicComponent : public LogicComponent {

	enum class eFillType {
		white, red
	};

public:
	RhythmLogicComponent();
	~RhythmLogicComponent();

	void SpacePressed() override;

	void Update() override;
	void OnAddToWorld() override;

	virtual std::vector<Note*> extractData() override;
	void recieveData(std::vector<Note*> notes) override;
private:
	// The 4 bars represented in the screen
	std::vector<Note*> notes[4];
	std::vector<float> beats[4];
	std::vector<GameEngine::Entity*> entities[4];
	int current;
	int bpm;

	float lastTick;

	float DistanceToNearestNote(float secs);
	void renderQuadNotes(int quad);
	void generateParticle(eFillType type);

	// Reference to the highlight sprite entity
	GameEngine::Entity * m_sprite;
};