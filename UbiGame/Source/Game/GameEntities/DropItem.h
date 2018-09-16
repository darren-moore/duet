#pragma once
#include "GameEngine/EntitySystem/Entity.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "Game/GameComponents/PhysicsIntegratorComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/GameComponents/TriggerColliderComponent.h"

namespace Game {
	class DropItemEntity : public GameEngine::Entity {
	public:
		DropItemEntity();
		~DropItemEntity();

		virtual void OnAddToWorld() override {};
		virtual void OnRemoveFromWorld() override {};

	protected:
		GameEngine::SpriteRenderComponent* m_renderComponent;
		Game::AccelerationComponent* m_accelerationComponent;
		Game::VelocityComponent* m_velocityComponent;
		Game::PhysicsIntegratorComponent* m_physicsIntegratorComponent;
		Game::TriggerColliderComponent* m_triggerColliderComponent;


		//GameEngine::AnimationComponent* m_animComponent;


	};

}