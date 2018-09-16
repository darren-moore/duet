#include "DropItem.h"

using namespace Game;
DropItemEntity::DropItemEntity() {
	//Render 
	m_renderComponent = static_cast<GameEngine::SpriteRenderComponent*>(AddComponent<GameEngine::SpriteRenderComponent>());
	m_renderComponent->SetTexture(GameEngine::eTexture::Player);
	m_renderComponent->SetZLevel(2);

	//Physics
	m_velocityComponent = static_cast<Game::VelocityComponent*>(AddComponent<Game::VelocityComponent>());
	m_accelerationComponent = static_cast<Game::AccelerationComponent*>(AddComponent<Game::AccelerationComponent>());
	m_accelerationComponent->acceleration = sf::Vector2f(0, 650);
	m_physicsIntegratorComponent = static_cast<Game::PhysicsIntegratorComponent*>(AddComponent<Game::PhysicsIntegratorComponent>());

	//Animation
	//m_animComponent = static_cast<GameEngine::AnimationComponent*>(AddComponent<GameEngine::AnimationComponent>());

	//Collisions
	AddComponent<Game::TriggerColliderComponent>();

	//Particles
	//GameEngine::ParticleEmitterComponent* emitterComponent = static_cast<GameEngine::ParticleEmitterComponent*>(AddComponent<GameEngine::ParticleEmitterComponent>());
	//GameEngine::SParticleDefinition particleDef = GameEngine::SParticleDefinition(GameEngine::eTexture::Particles, 1, sf::Vector2f(32.f, 32.f), GameEngine::EAnimationId::Smoke, 1.f);
	//emitterComponent->SetParticleDefinition(particleDef);


	//Sound
	//GameEngine::SoundComponent* const soundComponent = static_cast<GameEngine::SoundComponent*>(AddComponent<GameEngine::SoundComponent>());
	//soundComponent->SetNumSimultaneousSounds(2); // Hard coded 5 simultaneous sounds for the player

	//AddComponent<PlayerSoundComponent>();

	////Camera control
	//AddComponent<PlayerCameraComponent>();

}

DropItemEntity::~DropItemEntity() {

}

void DropItemEntity::OnAddToWorld() {
	__super::OnAddToWorld();
}

void DropItemEntity::OnRemoveFromWorld() {
	__super::OnRemoveFromWorld();
}