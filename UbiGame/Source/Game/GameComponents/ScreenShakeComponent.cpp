#include "ScreenShakeComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/Util/CameraManager.h"

#include <random>
#include <iostream>

ScreenShakeComponent::ScreenShakeComponent() 
	: m_lifetime(1.f)
	, m_initialtime(1.f) 
{
	
}

ScreenShakeComponent::~ScreenShakeComponent() {
	GameEngine::CameraManager::GetInstance()->GetCameraView().setCenter(center_x, center_y);
}

void ScreenShakeComponent::Update() {
	Component::Update();
	
	if (m_lifetime > 0.f) {
		float dt = GameEngine::GameEngineMain::GetInstance()->GetTimeDelta();

		// Do the actual screenshake
		float intensity = m_lifetime / m_initialtime;
		float x_offset = static_cast<float>(rand() % SHAKE_MULTIPLIER - SHAKE_MULTIPLIER / 2) * intensity;
		float y_offset = static_cast<float>(rand() % SHAKE_MULTIPLIER - SHAKE_MULTIPLIER / 2) * intensity;

		GameEngine::CameraManager::GetInstance()->GetCameraView().setCenter(center_x + x_offset, center_y + y_offset);

		m_lifetime -= dt;
	}
	else {
		// Just do nothing, should not cost too much overhead
	}
}

void ScreenShakeComponent::OnAddToWorld() {
	Component::OnAddToWorld();
}
