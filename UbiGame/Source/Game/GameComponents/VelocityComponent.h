/*
Holds velocity data for an entity.
*/

#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine\GameEngineMain.h"

namespace Game {
	class VelocityComponent : public GameEngine::Component {
	public:
		VelocityComponent() {};
		~VelocityComponent() {};

		sf::Vector2f velocity = sf::Vector2f(0,0);
	};
}