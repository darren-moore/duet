#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Game/Util/Note.h"
#include <SFML/System/Vector2.hpp>
#include "GameEngine/EntitySystem/Entity.h"

namespace Game {
	namespace MusicNoteUtils {
		std::vector<Note*> parseMusic(std::string musicString);
		std::vector<float> convertNotesToBeatTimes(std::vector<Note*> notes, int bpm);
		std::vector<GameEngine::Entity*> prepareNoteEntities(std::vector<Note*> notes, sf::Vector2f initPos);
		void moveNoteEntities(std::vector<GameEngine::Entity*> entities, sf::Vector2f pos);
		void assignStemTypes(std::vector<Note*> notes);
	}
}