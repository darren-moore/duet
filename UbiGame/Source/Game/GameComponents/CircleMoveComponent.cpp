#include "CircleMoveComponent.h"

#include <GameEngine/EntitySystem/Entity.h>

#include "../GameEntities/Ticker.h"

#include <cmath>

CircleMoveComponent::CircleMoveComponent() 
	: ticker(nullptr) 
	, radius(10.f)
	, original_x(0.f)
	, original_y(0.f)
	, x_operation(CircleMoveOperation::sin)
	, y_operation(CircleMoveOperation::cos)
{

}

CircleMoveComponent::~CircleMoveComponent() {

}

void CircleMoveComponent::Update() {
	float max = 4.f * 60.f / static_cast<float>(ticker->getBPM());
	float cur = ticker->getCurrentBarTick() / max;
	// calculate x and y positions
	float x_offset = 0.f, y_offset = 0.f;
	switch (x_operation) {
	case (CircleMoveOperation::sin): {
		x_offset = static_cast<float>(std::sin(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::negative_sin): {
		x_offset = static_cast<float>(-std::sin(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::cos): {
		x_offset = static_cast<float>(std::cos(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::negative_cos): {
		x_offset = static_cast<float>(-std::cos(cur * 2 * M_PI)) * radius;
	} break;
	}
	switch (y_operation) {
	case (CircleMoveOperation::sin): {
		y_offset = static_cast<float>(std::sin(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::negative_sin): {
		y_offset = static_cast<float>(-std::sin(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::cos): {
		y_offset = static_cast<float>(std::cos(cur * 2 * M_PI)) * radius;
	} break;
	case (CircleMoveOperation::negative_cos): {
		y_offset = static_cast<float>(-std::cos(cur * 2 * M_PI)) * radius;
	} break;
	}
	this->GetEntity()->SetPos(sf::Vector2f(original_x + x_offset, original_y + y_offset));
}

void CircleMoveComponent::OnAddToWorld() {
	this->GetEntity()->SetPos(sf::Vector2f(original_x, original_y + radius));
}
