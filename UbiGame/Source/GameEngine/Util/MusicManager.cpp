
#include "MusicManager.h"


#include <string>
#include <sstream>
#include <vector>
#include <iterator>

using namespace GameEngine;
using namespace std;

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
		if (ns.size() == 1) {
			n = new Note((Note::eNoteLength)(ns[0]-48), Note::eStemType::none, true, false, false);
		}
		if (ns.size() == 2) {
			if (ns[1] == '.') {
				n = new Note((Note::eNoteLength)(ns[0] - 48), Note::eStemType::none, true, true, false);
			}
			else {
				n = new Note((Note::eNoteLength)(ns[1] - 48), Note::eStemType::none, true, false, true);
			}
		}
		if (ns.size() == 3) {
			n = new Note((Note::eNoteLength)(ns[1] - 48), Note::eStemType::none, true, true, true);
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
		float noteTime = 1.f / note->noteLength;
		noteTime /= (bpm / 60);
		currentTime += noteTime;
	}

	float endFinalNote = currentTime;
	beatTimes.push_back(endFinalNote);

	return beatTimes;
}
