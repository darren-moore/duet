#include "LogicComponent.h"

#include <GameEngine/EntitySystem/Entity.h>
#include <GameEngine/EntitySystem/Components/SpriteRenderComponent.h>
#include <GameEngine/EntitySystem/Components/ParticleComponent.h>

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


void LogicComponent::generateParticle(eFillType type) {
	GameEngine::Entity* fill = new GameEngine::Entity();
	// Setup the sprite for the fill
	GameEngine::SpriteRenderComponent* render = static_cast<GameEngine::SpriteRenderComponent*>(fill->AddComponent<GameEngine::SpriteRenderComponent>());
	if (type == eFillType::white) render->SetTexture(GameEngine::eTexture::TapParticle);
	if (type == eFillType::red) render->SetTexture(GameEngine::eTexture::MissParticle);
	render->SetZLevel(20);
	fill->SetPos(sf::Vector2f(640.f, 360.f));
	fill->SetSize(sf::Vector2f(1280.f, 720.f));

	GameEngine::AnimationComponent* anim = static_cast<GameEngine::AnimationComponent*>(fill->AddComponent<GameEngine::AnimationComponent>());
	if (type == eFillType::white) anim->PlayAnim(EAnimationId::FillHit);
	if (type == eFillType::red) anim->PlayAnim(EAnimationId::FillMiss);

	// Set the lifetime for the fill to dissapear after 100 milliseconds
	GameEngine::ParticleComponent* part = static_cast<GameEngine::ParticleComponent*>(fill->AddComponent<GameEngine::ParticleComponent>());
	part->SetLifeTime(0.1f);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(fill);
}
