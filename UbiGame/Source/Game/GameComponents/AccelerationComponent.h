#pragma once
#include "GameEngine/EntitySystem/Component.h"
#include "GameEngine\GameEngineMain.h"

namespace Game {
	class AccelerationComponent : public GameEngine::Component {
	public:
		sf::Vector2f acceleration;
	};
}