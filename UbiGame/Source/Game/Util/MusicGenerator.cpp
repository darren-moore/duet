#include "MusicGenerator.h"
#include "Game/Util/MusicNoteUtils.h"
#include <fstream>
#include <stdio.h>
#include <ctime>

using namespace Game;

MusicGenerator::MusicGenerator() {
	srand(time(NULL));
	std::ifstream myfile(m_levelFileName);
	std::string line;
	if (myfile.is_open()) {
		while (std::getline(myfile, line)) {
			m_bars.push_back(MusicNoteUtils::parseMusic(line));
		}
		myfile.close();
	}
}


std::vector<Note*> MusicGenerator::getBarOfMusic() {
	return m_bars[rand() % m_bars.size()];
}

MusicGenerator MusicGenerator::m_instance;