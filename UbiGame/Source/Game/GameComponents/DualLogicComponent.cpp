#include "DualLogicComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "Game/GameComponents/PhysicsIntegratorComponent.h"
#include "Game/GameComponents/TriggerColliderComponent.h"
#include "Game/Util/MusicNoteUtils.h"
#include "Game/Util/MusicGenerator.h"

#include "Game/GameEntities/DropItem.h"

#include <iostream>

DualLogicComponent::DualLogicComponent() {
	// Add a background overlay
	overlay = new GameEngine::Entity();
	overlay->SetPos(sf::Vector2f(640.f, 360.f));
	overlay->SetSize(sf::Vector2f(1280.f, 720.f));
	GameEngine::SpriteRenderComponent* sprite = static_cast<GameEngine::SpriteRenderComponent*>(overlay->AddComponent<GameEngine::SpriteRenderComponent>());
	sprite->SetTexture(GameEngine::eTexture::DuelOverlay);
	sprite->SetZLevel(20);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(overlay);
}

DualLogicComponent::~DualLogicComponent() {
	for (auto e : m_noteEntities) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(e);
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(overlay);
}

void DualLogicComponent::SpacePressed() {
	std::cout << "DUAL LOGIC PRESSED!" << std::endl;
	GameEngine::Entity* e = new Game::DropItemEntity();
	e->SetPos(sf::Vector2f(100,100));
	e->SetSize(sf::Vector2f(32,32));
	GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
}

void DualLogicComponent::Update() {
	// logic for dropped item management.
}

void DualLogicComponent::OnAddToWorld() {

}

std::vector<Note*> DualLogicComponent::extractData() {
	// Return the data to be used upon state switching
	return std::vector<Note*>();
}

void DualLogicComponent::recieveData(std::vector<Note*> notes) {

	// Refresh notes with collision component.
	m_noteEntities = Game::MusicNoteUtils::prepareNoteEntities(notes, sf::Vector2f(notesPos, 200));

	for (auto e : m_noteEntities) {
		GameEngine::SpriteRenderComponent* rend = static_cast<GameEngine::SpriteRenderComponent*>(e->AddComponent<GameEngine::SpriteRenderComponent>());
		rend->SetTexture(GameEngine::eTexture::Highlight);
		rend->SetZLevel(1);
		Game::VelocityComponent* v = static_cast<Game::VelocityComponent*>(e->AddComponent<Game::VelocityComponent>());
		v->velocity = sf::Vector2f(-320, 0);
		e->AddComponent<Game::AccelerationComponent>();
		e->AddComponent<Game::PhysicsIntegratorComponent>();
		Game::TriggerColliderComponent* col = static_cast<Game::TriggerColliderComponent*>(e->AddComponent<Game::TriggerColliderComponent>());

		GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
	}
}
