#include "PhysicsIntegratorComponent.h"

using namespace Game;

void PhysicsIntegratorComponent::Update(){
	float dt = GameEngine::GameEngineMain::GetTimeDelta();
	sf::Vector2f* a = &GetEntity()->GetComponent<Game::AccelerationComponent>()->acceleration;
	sf::Vector2f* v = &GetEntity()->GetComponent<Game::VelocityComponent>()->velocity;
	*v += *a * dt;
	GetEntity()->SetPos(GetEntity()->GetPos() += *v * dt);
}
