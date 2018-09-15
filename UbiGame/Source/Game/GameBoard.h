#pragma once
#include "GameEngine\EntitySystem\Entity.h"

#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Game
{
	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();

		// Temp - for nice architecture this should be within some sort of IUpdatable interface that GameEngine handles (so that not only entities can be updated)
		void Update();

		// Temp - needed to match Game Engine interface
		bool IsGameOver() const { return false; }

	private:
		void CreateBackground();
	};
}

