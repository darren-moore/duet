#pragma once
#include "Game/Util/Note.h"
#include <string>
#include <vector>

namespace Game {
	class MusicGenerator {
	public:
		static MusicGenerator& instance() { return m_instance; }
		~MusicGenerator() {};

		std::vector<Note*> getBarOfMusic();

	private:
		MusicGenerator();

		static MusicGenerator m_instance;
		std::string m_levelFileName = "Resources/level/level_blocks.txt";
		std::vector<std::vector<Note*>> m_bars;

	};

}
