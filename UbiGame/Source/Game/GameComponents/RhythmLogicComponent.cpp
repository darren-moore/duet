#include "RhythmLogicComponent.h"

#include "GameEngine/GameEngineMain.h"
#include "Game/Util/MusicNoteUtils.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "Game/Util/MusicGenerator.h"

#include "../GameEntities/Ticker.h"

#include <iostream>

RhythmLogicComponent::RhythmLogicComponent()
	: notes{}
	, beats{}
	, current(0)
	, bpm(120)
	, lastTick(0.f)
	, entities{}
{

	for (int i = 0; i < 4; ++i) notes[i] = Game::MusicGenerator::instance().getBarOfMusic();
	for (int i = 0; i < 4; ++i) beats[i] = Game::MusicNoteUtils::convertNotesToBeatTimes(notes[i], bpm);
	
	// Add the highlights entity to the world
	m_sprite = new GameEngine::Entity();
	GameEngine::SpriteRenderComponent * rend = static_cast<GameEngine::SpriteRenderComponent*>(m_sprite->AddComponent<GameEngine::SpriteRenderComponent>());
	rend->SetTexture(GameEngine::eTexture::Highlight);
	rend->SetZLevel(1);
	GameEngine::GameEngineMain::GetInstance()->AddEntity(m_sprite);
}

RhythmLogicComponent::~RhythmLogicComponent() {
	GameEngine::GameEngineMain::GetInstance()->RemoveEntity(m_sprite);
	// Delete heap allocated things
	for (auto en : entities[0]) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(en);
	for (auto en : entities[1]) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(en);
	for (auto en : entities[2]) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(en);
	for (auto en : entities[3]) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(en);
}

void RhythmLogicComponent::SpacePressed() {
	// Get the difference from tap to nearest beat
	float dist = DistanceToNearestNote(ticker->getCurrentBarTick());
	if (dist < 0.1) {
		generateParticle(eFillType::white);
	}
	else {
		// TODO: make sure this isn't the first 
		generateParticle(eFillType::red);
	}
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
	std::vector<Note*> data;
	data.reserve(notes[0].size() + notes[1].size() + notes[2].size() + notes[3].size());
	data.insert(data.end(), notes[0].begin(), notes[0].end());
	data.insert(data.end(), notes[1].begin(), notes[1].end());
	data.insert(data.end(), notes[2].begin(), notes[2].end());
	data.insert(data.end(), notes[3].begin(), notes[3].end());
	// Return the data to be used upon state switching
	return data;
}

void RhythmLogicComponent::recieveData(std::vector<Note*> notes) {
	// Do something with this data
	int count = 0;
	int current_index = 0;
	for (Note * n : notes) {
		this->notes[current_index].push_back(n);
		count += n->noteLength;
		// If we have now counted for more than a bar, switch to the next bar
		if (count >= 16) {
			count = 0;
			current_index++;
			// Error prevention lmao
			if (current_index >= 4) break;
		}
	}
}

float RhythmLogicComponent::DistanceToNearestNote(float secs) {
	// Since we are assuming no rests for now, can safely assume 0 will be a beat
	float min = secs;
	for (float beat : beats[current]) {
		if (std::abs(beat - secs) < min) {
			min = std::abs(beat - secs);
		}
	}
	std::cout << "HIT @ " << secs << ", " << "MIN @ " << min << std::endl;
	return min;
}

void RhythmLogicComponent::renderQuadNotes(int quad) {
	// Delete the previous quad notes
	for (auto en : entities[quad]) GameEngine::GameEngineMain::GetInstance()->RemoveEntity(en);
	entities[quad].clear();

	// Adds note entities to render
	std::vector<GameEngine::Entity*> noteEntities = Game::MusicNoteUtils::prepareNoteEntities(notes[quad], sf::Vector2f(640, 200));
	for (auto ne : noteEntities) {
		GameEngine::GameEngineMain::GetInstance()->AddEntity(ne);
		entities[quad].push_back(ne);
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