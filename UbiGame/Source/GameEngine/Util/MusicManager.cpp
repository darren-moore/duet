
#include "MusicManager.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "GameEngine/GameEngineMain.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace GameEngine;
using namespace std;

// String splitting from https://stackoverflow.com/a/236803
template<typename Out>
void split(const std::string &s, char delim, Out result) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		*(result++) = item;
	}
}

std::vector<std::string> split(const std::string &s, char delim){
	std::vector<std::string> elems;
	split(s, delim, std::back_inserter(elems));
	return elems;
}

vector<Note*> MusicManager::parseMusic(std::string musicString) {
	vector<string> noteStrings = split(musicString, ' ');
	vector<Note*> notes;
	for (const auto& ns : noteStrings) {
		Note* n;
		if (ns[0] == '_') {
			n = new Note(stoi(ns.substr(1,ns.size() - 1)), Note::eStemType::none, true, true);
		}
		else {
			n = new Note(stoi(ns), Note::eStemType::none, true, false);
		}
		notes.push_back(n);
	}


	return notes;
}

// Convert to beat times, starting at 0. The last element denotes the time of the end of the note.
vector<float> MusicManager::convertNotesToBeatTimes(vector<Note*> notes, int bpm) {
	vector<float> beatTimes;
	float currentTime = 0;
	for (auto note : notes) {
		if (!note->isRest) {
			beatTimes.push_back(currentTime);
		}
		float noteTime = (note->noteLength)/16.f;
		noteTime /= (bpm / 60);
		currentTime += noteTime;
	}

	float endFinalNote = currentTime;
	beatTimes.push_back(endFinalNote);

	return beatTimes;
}


vector<Entity*> MusicManager::prepareNoteEntities(vector<Note*> notes, sf::Vector2f initPos) {
	int position = (int)initPos.x;
	vector<Entity*> noteEntities;
	for (auto n : notes) {
		GameEngine::Entity* e = new GameEngine::Entity();
		Game::NoteRenderComponent* renderComponent = static_cast<Game::NoteRenderComponent*>(e->AddComponent<Game::NoteRenderComponent>());
		renderComponent->SetTexture(GameEngine::eTexture::Player);
		renderComponent->SetZLevel(2);

		renderComponent->setNote(n);
		position += n->noteLength * 40 / 2;
		e->SetPos(sf::Vector2f((float)position, initPos.y));
		e->SetSize(sf::Vector2f(30, 30));
		noteEntities.push_back(e);

		position += n->noteLength * 40 / 2;
	}

	return noteEntities;
}

void MusicManager::moveNoteEntities(vector<Entity*> entities, sf::Vector2f pos) {
	int position = (int)pos.x;
	for (auto e : entities) {
		Note* note = e->GetComponent<Game::NoteRenderComponent>()->getNote();
		position += note->noteLength * 40 / 2;
		e->SetPos(sf::Vector2f((float)position, pos.y));
		e->SetSize(sf::Vector2f(30, 30));
		position += note->noteLength * 40 / 2;
	}

}