#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Game/Util/Note.h"
#include <SFML/System/Vector2.hpp>
#include "GameEngine/EntitySystem/Entity.h"

namespace GameEngine {
	class MusicManager {
	public:
		static std::vector<Note*> parseMusic(std::string musicString);
		static std::vector<float> convertNotesToBeatTimes(std::vector<Note*> notes, int bpm);
		static std::vector<Entity*> prepareNoteEntities(std::vector<Note*> notes, sf::Vector2f initPos);
		static void MusicManager::moveNoteEntities(std::vector<Entity*> entities, sf::Vector2f pos);
		static void assignStemTypes(std::vector<Note*> notes);
	};

}
