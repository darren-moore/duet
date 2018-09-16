/*
Component that moves an entity in a circular fashion
*/

#pragma once
#include <GameEngine/EntitySystem/Component.h>

#define _USE_MATH_DEFINES

class Ticker;

enum class CircleMoveOperation {
	sin,
	negative_sin,
	cos,
	negative_cos
};

class CircleMoveComponent : public GameEngine::Component {

public:

	CircleMoveComponent();
	~CircleMoveComponent();

	inline void setTicker(Ticker * ticker) { this->ticker = ticker; }
	inline void setRadius(float radius) { this->radius = radius; }
	inline void setOriginalPos(float x, float y) { original_x = x, original_y = y; }
	inline void setXOperation(CircleMoveOperation op) { this->x_operation = op; }
	inline void setYOperation(CircleMoveOperation op) { this->y_operation = op; }

	void Update() override;
	void OnAddToWorld() override;

private:

	// Keep a ticker reference to update cloud movement according to music
	Ticker * ticker;

	float radius;
	float original_x, original_y;
	CircleMoveOperation x_operation, y_operation;

};