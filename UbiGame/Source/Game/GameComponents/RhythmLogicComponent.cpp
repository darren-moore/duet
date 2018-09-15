#include "RhythmLogicComponent.h"
#include "../GameEntities/Ticker.h"

#include <iostream>

RhythmLogicComponent::RhythmLogicComponent() 
	: bars{}
	, current(0)
{
	// Initialize all the bars to have 4/4 for now
	for (int i = 0; i < 4; ++i) bars[i] = std::vector<float>(4, 4.f);
}

RhythmLogicComponent::~RhythmLogicComponent() {
	
}

void RhythmLogicComponent::SpacePressed() {
	std::cout << "RHYTHM LOGIC PRESSED @ " << ticker->getCurrentBarTick() << std::endl;
}

void RhythmLogicComponent::Update() {

}

void RhythmLogicComponent::OnAddToWorld() {

}
