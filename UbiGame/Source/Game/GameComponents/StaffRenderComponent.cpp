#include "StaffRenderComponent.h"

using namespace Game;

void StaffRenderComponent::Render(sf::RenderTarget* target) {
	// Draw two sets of 5 lines.
	renderStaff(target, sf::Vector2f(0, 200.f));
	renderStaff(target, sf::Vector2f(0, 400.f));

}


void StaffRenderComponent::renderStaff(sf::RenderTarget* target, sf::Vector2f topLeft) {
	
	for (int y = 0; y < 5; y++) {
		sf::RectangleShape line = sf::RectangleShape();

		line.setSize(sf::Vector2f(1280.f, 2.f));
		line.setPosition(topLeft.x, topLeft.y + y*20.f);

		sf::Color col = sf::Color(255, 255, 255);
		col.b = 255;
		line.setFillColor(col);
		target->draw(line);
	}
	sf::RectangleShape barLine = sf::RectangleShape();

	barLine.setSize(sf::Vector2f(2.f, 80.f));
	barLine.setPosition(1280/2.f, topLeft.y);

	sf::Color col = sf::Color(255, 255, 255);
	col.b = 255;
	barLine.setFillColor(col);
	target->draw(barLine);
}
