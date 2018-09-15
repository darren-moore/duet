#pragma once
#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

namespace Game {
	class TriggerColliderComponent : public GameEngine::CollidableComponent {
	public:

		void Update();
	};

}
