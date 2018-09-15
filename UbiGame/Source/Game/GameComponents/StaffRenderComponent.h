#pragma once

#include "GameEngine/EntitySystem/Components/RenderComponent.h"

namespace Game {
	class StaffRenderComponent : public GameEngine::RenderComponent {
	public:
		void Render(sf::RenderTarget* target);

	private:
		void renderStaff(sf::RenderTarget* target, sf::Vector2f topLeft);

	};
}