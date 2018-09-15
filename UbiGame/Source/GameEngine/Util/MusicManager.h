#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Game/Util/Note.h"

namespace GameEngine {
	class MusicManager {
	public:
		static std::vector<Note*> parseMusic(std::string musicString);
		static std::vector<float> convertNotesToBeatTimes(std::vector<Note*> notes, int bpm);
	};

}
