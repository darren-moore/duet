#include "DualLogicComponent.h"

#include <iostream>

DualLogicComponent::DualLogicComponent() {

}

DualLogicComponent::~DualLogicComponent() {

}

void DualLogicComponent::SpacePressed() {
	std::cout << "DUAL LOGIC PRESSED!" << std::endl;
}

void DualLogicComponent::Update() {

}

void DualLogicComponent::OnAddToWorld() {

}

std::vector<Note*> DualLogicComponent::extractData() {
	// Return the data to be used upon state switching
	return std::vector<Note*>();
}

void DualLogicComponent::recieveData(std::vector<Note*> notes) {
	// Do something with this data
}
