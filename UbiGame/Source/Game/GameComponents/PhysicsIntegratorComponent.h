/*
Integrates velocity and position with semi-implicit time integration.
*/

#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "GameEngine\GameEngineMain.h"

namespace Game {
	class PhysicsIntegratorComponent : public GameEngine::Component {
	public:
		PhysicsIntegratorComponent();
		~PhysicsIntegratorComponent();

		void Update();
	};
}