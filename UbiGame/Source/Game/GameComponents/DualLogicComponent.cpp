#include "DualLogicComponent.h"
#include "GameEngine/GameEngineMain.h"
#include "Game/Util/MusicNoteUtils.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/GameComponents/VelocityComponent.h"
#include "Game/GameComponents/AccelerationComponent.h"
#include "Game/GameComponents/PhysicsIntegratorComponent.h"
#include "Game/GameComponents/TriggerColliderComponent.h"

#include "Game/GameEntities/DropItem.h"

#include <iostream>

DualLogicComponent::DualLogicComponent() {

}

DualLogicComponent::~DualLogicComponent() {

}

void DualLogicComponent::SpacePressed() {
	std::cout << "DUAL LOGIC PRESSED!" << std::endl;
	//GameEngine::Entity* e = new Game::DropItemEntity();
	//e->SetPos(sf::Vector2f(10,10));
	//e->SetSize(sf::Vector2f(30,30));
}

void DualLogicComponent::Update() {
	Game::MusicNoteUtils::moveNoteEntities(m_noteEntities, sf::Vector2f(notesPos, 200));
	notesPos -= 1;
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
		v->velocity = sf::Vector2f(-5, 0);
		e->AddComponent<Game::AccelerationComponent>();
		e->AddComponent<Game::PhysicsIntegratorComponent>();
		Game::TriggerColliderComponent* col = static_cast<Game::TriggerColliderComponent*>(e->AddComponent<Game::TriggerColliderComponent>());

		GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
	}
}
