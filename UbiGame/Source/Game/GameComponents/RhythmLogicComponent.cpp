#include "RhythmLogicComponent.h"
#include "../GameEntities/Ticker.h"

#include <iostream>

RhythmLogicComponent::RhythmLogicComponent()
	: bars{}
	, current(0)
	, bpm(120)
{
	// Initialize all the bars to have 4/4 for now
	for (int i = 0; i < 4; ++i) bars[i] = std::vector<float>(8, 2.f);
}

RhythmLogicComponent::~RhythmLogicComponent() {
	
}

void RhythmLogicComponent::SpacePressed() {
	float secs = ticker->getCurrentBarTick();
	float beats = bpm * secs / 60.f;
	float sixteenths = beats * 4.0f;
	std::cout << "RHYTHM LOGIC PRESSED @ " << sixteenths << ", nearest: " << DistanceToNearestNote(sixteenths) << std::endl;
}

void RhythmLogicComponent::Update() {
	
}

void RhythmLogicComponent::OnAddToWorld() {

}

float RhythmLogicComponent::DistanceToNearestNote(float beat) {
	// Since we are assuming no rests for now, can safely assume 0 will be a beat
	float min = beat;
	float total = 0;
	for (int i = 0; i < bars[current].size() - 1; ++i) {
		total += bars[current][i];
		if (std::abs(total - beat) < min) {
			min = std::abs(total - beat);
		}
	}
	return min;
}
