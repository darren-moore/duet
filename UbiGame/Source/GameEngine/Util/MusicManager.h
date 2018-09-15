#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Game/Util/Note.h"
#include <SFML/System/Vector2.hpp>

namespace GameEngine {
	class MusicManager {
	public:
		static std::vector<Note*> parseMusic(std::string musicString);
		static std::vector<float> convertNotesToBeatTimes(std::vector<Note*> notes, int bpm);
		static void positionNotes(std::vector<Note*> notes, sf::Vector2f barSize);
	};

}
