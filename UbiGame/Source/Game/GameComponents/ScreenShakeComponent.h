/*
Contains logic for a screen shake
*/

#pragma once
#include "GameEngine/EntitySystem/Component.h"

#define SHAKE_MULTIPLIER 20

class ScreenShakeComponent : public GameEngine::Component {

public:
	ScreenShakeComponent();
	~ScreenShakeComponent();

	inline void setCenter(float x, float y) { center_x = x, center_y = y; }
	inline void setTime(float time) { m_lifetime = time, m_initialtime = time; }

	void Update() override;
	void OnAddToWorld() override;

private:

	float center_x, center_y;
	float m_lifetime;
	float m_initialtime;

};
