#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Game/Util/Note.h"

namespace GameEngine {
	class MusicManager {
	public:
		std::unordered_map<char, Note::eNoteLength> noteCharToNoteLength = 
		{ {'1', Note::eNoteLength::whole} };
		std::string m = "8 4 2";
		static std::vector<Note*> parseMusic(std::string musicString);
		static std::vector<float> convertNotesToBeatTimes(std::vector<Note*> notes, int bpm);
	};

}
