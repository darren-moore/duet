#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "GameEngine\GameEngineMain.h"

namespace Game {
	class PhysicsIntegratorComponent : public GameEngine::Component {
	public:

		void Update() {
			float dt = GameEngine::GameEngineMain::GetTimeDelta();
			sf::Vector2f* a = &GetEntity()->GetComponent<Game::AccelerationComponent>()->acceleration;
			sf::Vector2f* v = &GetEntity()->GetComponent<Game::VelocityComponent>()->velocity;
			*v += *a * dt;
			GetEntity()->SetPos(GetEntity()->GetPos() += *v * dt);
		}
	};
}