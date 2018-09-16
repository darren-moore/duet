#include "LogicComponent.h"

using namespace GameEngine;

// Require a ticker for the logic components
LogicComponent::LogicComponent() : ticker(nullptr) {
	// Empty stub in base class
}

LogicComponent::~LogicComponent() {
	// Empty stub in base class
}

void LogicComponent::SpacePressed() {
	// Empty stub in base class
}

void LogicComponent::Update() {
	// Empty stub in base class
}

void LogicComponent::OnAddToWorld() {
	// Empty stub in base class
}

std::vector<Note*> LogicComponent::extractData() {
	return std::vector<Note*>();
}

void LogicComponent::recieveData(std::vector<Note*> notes) {
	// Empty stub in base class
}
