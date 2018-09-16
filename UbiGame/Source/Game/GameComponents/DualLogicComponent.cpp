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

#include "../GameEntities/Ticker.h"
#include "../GameEntities/Controller.h"

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
	for (auto& eBar : entities) {
		for (auto e : eBar) {
			GameEngine::GameEngineMain::GetInstance()->RemoveEntity(e);
		}
	}

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

	// We know the bar reset if the ticker tick is less than the last tick
	if (ticker->getCurrentBarTick() < lastTick) {
		// Update the current bar as well
		if (!halfTimeFlag) {
			halfTimeFlag = true;
		}
		else {
			halfTimeFlag = false;
			// delete first bar, now hidden
			std::vector<GameEngine::Entity*> toRemove = entities[0];
			for (auto e : toRemove) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(e);
			entities.erase(entities.begin());

			toRemove = entities[2];
			for (auto e : toRemove) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(e);
			entities.erase(entities.begin() + 2);
			entities.insert(entities.begin() + 2, Game::MusicNoteUtils::prepareNoteEntities(Game::MusicGenerator::instance().getBarOfMusic(), topSpawnPoint));
			for (auto e : entities[2]) {
				processNoteEntitiy(e);
				e->GetComponent<Game::VelocityComponent>()->velocity.x *= -1;
			}

			// create new 5th bar, about to be revealed
			std::vector<GameEngine::Entity*> newEnts = Game::MusicNoteUtils::prepareNoteEntities(Game::MusicGenerator::instance().getBarOfMusic(), bottomSpawnPoint);
			for (auto e : newEnts) processNoteEntitiy(e);
			entities.push_back(newEnts);
		}
	}
	lastTick = ticker->getCurrentBarTick();

	// Update highlight position based on current quad


}

void DualLogicComponent::OnAddToWorld() {

}

std::vector<Note*> DualLogicComponent::extractData() {
	// Return the data to be used upon state switching
	return std::vector<Note*>();
}

void DualLogicComponent::recieveData(std::vector<Note*> notesIn) {
	int count = 0;
	int current_index = 0;
	std::vector<Note*> notesArray[4];
	for (Note * n : notesIn) {
		notesArray[current_index].push_back(n);
		count += n->noteLength;
		// If we have now counted for more than a bar, switch to the next bar
		if (count >= 16) {
			count = 0;
			current_index++;
			// Error prevention lmao
			if (current_index >= 4) break;
		}
	}
	notes.push_back(notesArray[0]);
	notes.push_back(notesArray[1]);
	notes.push_back(notesArray[2]);
	notes.push_back(notesArray[2]);
	notes.push_back(notesArray[3]);
	notes.push_back(Game::MusicGenerator::instance().getBarOfMusic());


	// Refresh notes with collision component.
	//m_noteEntities = Game::MusicNoteUtils::prepareNoteEntities(notes, sf::Vector2f(notesPos, 200));
	for (int i = 0; i < 6; i++) {
		std::vector<GameEngine::Entity*> noteEntities = Game::MusicNoteUtils::prepareNoteEntities(notes[i], sf::Vector2f(0,0));
		switch (i)
		{
		case 0:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(0, 200));
			break;
		case 1:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(640, 200));
			break;
		case 2:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(1280, 200));
			break;
		case 3:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(640, 400));
			break;
		case 4:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(0, 400));
			break;
		case 5:
			Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(-640, 400));
			break;
		default:
			break;
		}
		for (auto e : noteEntities) {
			processNoteEntitiy(e);
			if (i < 3) {
				e->GetComponent<Game::VelocityComponent>()->velocity.x *= -1;
			}
			GameEngine::GameEngineMain::GetInstance()->AddEntity(e);
		}
		entities.push_back(noteEntities);
	}

}

void DualLogicComponent::processNoteEntitiy(GameEngine::Entity* e) {
	GameEngine::SpriteRenderComponent* rend = static_cast<GameEngine::SpriteRenderComponent*>(e->AddComponent<GameEngine::SpriteRenderComponent>());
	rend->SetTexture(GameEngine::eTexture::Note);
	rend->SetZLevel(3);
	Game::VelocityComponent* v = static_cast<Game::VelocityComponent*>(e->AddComponent<Game::VelocityComponent>());
	v->velocity = sf::Vector2f(160, 0);
	e->AddComponent<Game::AccelerationComponent>();
	e->AddComponent<Game::PhysicsIntegratorComponent>();
	Game::TriggerColliderComponent* col = static_cast<Game::TriggerColliderComponent*>(e->AddComponent<Game::TriggerColliderComponent>());
}