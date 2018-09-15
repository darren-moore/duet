/*
Holds acceleration data for an entity.
*/

#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine/GameEngineMain.h"

namespace Game {
	class AccelerationComponent : public GameEngine::Component {
	public:
		AccelerationComponent() {};
		~AccelerationComponent() {};

		sf::Vector2f acceleration;
	};
}
