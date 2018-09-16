#include "RhythmLogicComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "Game/Util/MusicNoteUtils.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"

#include "../GameEntities/Ticker.h"

#include <iostream>

RhythmLogicComponent::RhythmLogicComponent()
	: notes{}
	, beats{}
	, current(0)
	, bpm(120)
	, lastTick(0.f)
{
	// Initialize all the bars to have 4/4 for now
	for (int i = 0; i < 4; ++i) notes[i] = Game::MusicNoteUtils::parseMusic("0,4 5,4 10,4 14,4");
	for (int i = 0; i < 4; ++i) beats[i] = Game::MusicNoteUtils::convertNotesToBeatTimes(notes[i], bpm);
	// Add the highlights entity to the world
	m_sprite = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent * rend = static_cast<GameEngine::SpriteRenderComponent*>(m_sprite->AddComponent<GameEngine::SpriteRenderComponent>());
	rend->SetTexture(GameEngine::eTexture::Highlight);
	rend->SetZLevel(1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_sprite);
}

RhythmLogicComponent::~RhythmLogicComponent() {
	
}

void RhythmLogicComponent::SpacePressed() {
	float secs = ticker->getCurrentBarTick();
	std::cout << "RHYTHM LOGIC PRESSED @ " << secs << ", nearest: " << DistanceToNearestNote(secs) << std::endl;
}

void RhythmLogicComponent::Update() {
	// We know the bar reset if the ticker tick is less than the last tick
	if (ticker->getCurrentBarTick() < lastTick) {
		// Update the current bar as well
		current++;
		if (current >= 4) current = 0;
	}
	lastTick = ticker->getCurrentBarTick();

	// Update highlight position based on current quad
	if (current == 0) m_sprite->SetPos(sf::Vector2f( 320.f, 200.f));
	if (current == 1) m_sprite->SetPos(sf::Vector2f( 640.f + 320.f, 200.f));
	if (current == 2) m_sprite->SetPos(sf::Vector2f( 320.f, 400.f));
	if (current == 3) m_sprite->SetPos(sf::Vector2f( 640.f + 320.f, 400.f));
}

void RhythmLogicComponent::OnAddToWorld() {
	// Add renderable components of the notes to the engine
	for (int i = 0; i < 4; ++i) renderQuadNotes(i);
}

std::vector<Note*> RhythmLogicComponent::extractData() {
	// Return the data to be used upon state switching
	return std::vector<Note*>();
}

void RhythmLogicComponent::recieveData(std::vector<Note*> notes) {
	// Do something with this data
}

float RhythmLogicComponent::DistanceToNearestNote(float beat) {
	// Since we are assuming no rests for now, can safely assume 0 will be a beat
	float min = beat;
	float total = 0;
	for (int i = 0; i < beats[current].size() - 1; ++i) {
		total += beats[current][i];
		if (std::abs(total - beat) < min) {
			min = std::abs(total - beat);
		}
	}
	return min;
}

void RhythmLogicComponent::renderQuadNotes(int quad) {
	// Adds note entities to render
	std::vector<GameEngine::Entity*> noteEntities = Game::MusicNoteUtils::prepareNoteEntities(notes[quad], sf::Vector2f(640, 200));
	for (auto ne : noteEntities) {
		GameEngine::GameEngineMain::GetInstance()->AddEntity(ne);
	}
	switch (quad) {
	case 0: {
		Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(0, 200));
	} break;
	case 1: {
		Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(640, 200));
	} break;
	case 2: {
		Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(0, 400));
	} break;
	case 3: {
		Game::MusicNoteUtils::moveNoteEntities(noteEntities, sf::Vector2f(640, 400));
	} break;
	default: {
		// This should never happen...
	} break;
	}
}
