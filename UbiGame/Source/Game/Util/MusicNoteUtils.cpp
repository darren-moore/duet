
#include "MusicNoteUtils.h"
#include "Game/GameComponents/NoteRenderComponent.h"
#include "GameEngine/GameEngineMain.h"

#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace Game;
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

vector<Note*> MusicNoteUtils::parseMusic(std::string musicString) {
	vector<string> noteStrings = split(musicString, ' ');
	vector<Note*> notes;
	for (const auto& ns : noteStrings) {
		Note* n;
		if (ns[0] == '_') {	// It's a rest.
			n = new Note(stoi(ns.substr(1, ns.size() - 1)), 0, Note::eStemType::none, 0, true, true);

		}
		else {	// Note, not a rest
			int delimPos = static_cast<int>(ns.find(','));
			string s1 = ns.substr(delimPos+1, ns.size() - 1);
			string s2 = ns.substr(0, delimPos);
			n = new Note(stoi(s1), stoi(s2), Note::eStemType::none, 0, true, false);
		}
		notes.push_back(n);
	}

	assignStemTypes(notes);
	return notes;
}

void MusicNoteUtils::assignStemTypes(vector<Note*> notes) {
	int endCheck = 0;
	int beatCounter = 0;

	bool inGroup = false;
	int initStemHeight = 75;
	int groupStartPitch = 0;
	int stemHeight = 75;
	
	for (int i = 0; i < notes.size(); i++) {
		endCheck += notes[i]->noteLength;

		if (notes[i]->noteLength >= 4) {
			notes[i]->stemType = Note::eStemType::none; //not in group
			stemHeight = initStemHeight;
			endCheck = endCheck % 4;
		}
		else {
			if (endCheck == 4) {
				if (i>0  && notes[i-1]->isRest) {
					notes[i]->stemType = Note::eStemType::halfStart; //not in group
					stemHeight = initStemHeight;
				}
				else if (i>0 && notes[i]->noteLength != notes[i - 1]->noteLength) {
					if (notes[i]->noteLength != 2) {
						notes[i]->stemType = Note::eStemType::halfEnd; //in group
						//if (!inGroup) stemHeight -= note->notePitch * 5.f;
					}
					else {
						notes[i]->stemType = Note::eStemType::end; //in group
					}
				}
				else {
					notes[i]->stemType = Note::eStemType::none; //in group
				}

				endCheck = 0;
			}

			// To check if first beat in a group, ask: endCheck == noteLength.
			else {
				if (i<notes.size()-1 && notes[i + 1]->noteLength == 3 || notes[i]->noteLength == 3) {
					notes[i]->stemType = Note::eStemType::halfStart; //in group
					stemHeight = initStemHeight - 5.f*(groupStartPitch - notes[i]->notePitch);
				}
				else if (i<notes.size()-1 && notes[i + 1]->isRest) {
					if (notes[i]->noteLength != 2) {
						notes[i]->stemType = Note::eStemType::start; //in group
						stemHeight = initStemHeight - 5.f*(groupStartPitch - notes[i]->notePitch);
					}
					else {
						notes[i]->stemType = Note::eStemType::halfStart; //not in group
						stemHeight = initStemHeight;
					}
				}
				else if(i<notes.size()-1 && notes[i + 1]->noteLength != notes[i]->noteLength) {
					if (notes[i]->noteLength == 1) {
						notes[i]->stemType = Note::eStemType::none; // in group
						stemHeight = initStemHeight - 5.f*(groupStartPitch - notes[i]->notePitch);
					}
					else {
						notes[i]->stemType = Note::eStemType::halfStart; //in group
						stemHeight = initStemHeight - 5.f*(groupStartPitch - notes[i]->notePitch);
					}
				
				}
				else {
					notes[i]->stemType = Note::eStemType::start; //in group
					stemHeight = initStemHeight - 5.f*(groupStartPitch - notes[i]->notePitch);
				}
				if (endCheck == notes[i]->noteLength) {
					groupStartPitch = notes[i]->notePitch;
				}
			}
		}
		notes[i]->stemHeight = 75;

	}
}

// Convert to beat times, starting at 0. The last element denotes the time of the end of the note.
vector<float> MusicNoteUtils::convertNotesToBeatTimes(vector<Note*> notes, int bpm) {
	vector<float> beatTimes;
	float currentTime = 0;
	for (auto note : notes) {
		if (!note->isRest) {
			beatTimes.push_back(currentTime);
		}
		float noteTime = (note->noteLength)/4.f;
		noteTime /= (bpm / 60);
		currentTime += noteTime;
	}

	float endFinalNote = currentTime;
	beatTimes.push_back(endFinalNote);

	return beatTimes;
}


vector<GameEngine::Entity*> MusicNoteUtils::prepareNoteEntities(vector<Note*> notes, sf::Vector2f initPos) {
	int position = (int)initPos.x;
	vector<GameEngine::Entity*> noteEntities;
	for (auto n : notes) {
		GameEngine::Entity* e = new GameEngine::Entity();
		Game::NoteRenderComponent* renderComponent = static_cast<Game::NoteRenderComponent*>(e->AddComponent<Game::NoteRenderComponent>());
		renderComponent->SetTexture(GameEngine::eTexture::Note);
		renderComponent->SetZLevel(5);

		renderComponent->setNote(n);
		position += n->noteLength * 40 / 2;
		e->SetPos(sf::Vector2f((float)position, initPos.y+50));// +n->notePitch * 5));
		e->SetSize(sf::Vector2f(32, 32));
		noteEntities.push_back(e);

		position += n->noteLength * 40 / 2;
	}

	return noteEntities;
}

void MusicNoteUtils::moveNoteEntities(vector<GameEngine::Entity*> entities, sf::Vector2f pos) {
	int position = (int)pos.x;
	for (auto e : entities) {
		Note* note = e->GetComponent<Game::NoteRenderComponent>()->getNote();
		position += note->noteLength * 40 / 2;
		e->SetPos(sf::Vector2f((float)position, pos.y+50));// +note->notePitch * 5.f));
		e->SetSize(sf::Vector2f(32, 32));
		position += note->noteLength * 40 / 2;
	}

}