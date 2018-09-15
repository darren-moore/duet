
#include "NoteRenderComponent.h"
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace GameEngine;


void NoteRenderComponent::Render(sf::RenderTarget* target) {
	if (m_note->isRest) {
		renderRest(target);
	}
	else {
		renderNote(target);
		renderStem(target);
	}

	if (m_note->isDotted) {
		renderDot(target);
	}

}

void NoteRenderComponent::renderNote(sf::RenderTarget* target) {
	sf::RectangleShape rect = sf::RectangleShape();

	rect.setSize(GetEntity()->GetSize());
	rect.setPosition(GetEntity()->GetPos());

	sf::Color col = sf::Color(100, 250, 50);
	col.b = 255;
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(2.f);

	rect.setOutlineColor(col);

	target->draw(rect);
}

void NoteRenderComponent::renderRest(sf::RenderTarget* target) {
	sf::RectangleShape rect = sf::RectangleShape();

	rect.setSize(sf::Vector2f(50.f, 50.f));
	rect.setPosition(sf::Vector2f(50.f, 50.f));

	sf::Color col = sf::Color(100, 50, 50);
	col.b = 255;
	rect.setFillColor(col);

	target->draw(rect);
}

void NoteRenderComponent::renderStem(sf::RenderTarget* target) {
	sf::RectangleShape rect = sf::RectangleShape();
	sf::Vector2f stemBase = GetEntity()->GetPos();
	if (m_note->isStemUp) {
		stemBase.x += GetEntity()->GetSize().x;
		rect.setPosition(sf::Vector2f(stemBase.x, stemBase.y - m_stemHeight/2 ));
	}
	else {
		stemBase.x -= GetEntity()->GetSize().x;
		rect.setPosition(sf::Vector2f(stemBase.x, stemBase.y + m_stemHeight/2 ));
	}

	rect.setSize(sf::Vector2f(10.f, m_stemHeight));


	sf::Color col = sf::Color(100, 50, 50);
	col.b = 255;
	rect.setFillColor(col);

	target->draw(rect);
}


void NoteRenderComponent::renderDot(sf::RenderTarget* target) {
	sf::CircleShape circ(2);

	circ.setPosition(GetEntity()->GetPos() + (GetEntity()->GetSize()/2.f));

	sf::Color col = sf::Color(100, 50, 250);
	col.b = 255;
	circ.setFillColor(col);

	target->draw(circ);
}

