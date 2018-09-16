
#include "NoteRenderComponent.h"
#include "GameEngine/EntitySystem/Entity.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

using namespace Game;


void NoteRenderComponent::Render(sf::RenderTarget* target) {

	
	if (!target)
	{
		return;
	}

	if (m_note->isRest) {
		__super::SetTexture(GameEngine::eTexture::QuarterRest);
		__super::UpdateSpriteParams();
		renderRest(target);
	}
	else {
		__super::SetTexture(GameEngine::eTexture::Note);
		__super::UpdateSpriteParams();
		renderStem(target);
	}

	if (m_note->isDotted) {
		renderDot(target);
	}

	__super::Render(target);

}

// TODO
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
		stemBase.x += GetEntity()->GetSize().x/2;
		stemBase.y -= m_note->stemHeight;
		rect.setPosition(stemBase);
	}
	else {
		stemBase.x -= GetEntity()->GetSize().x / 2;
		rect.setPosition(stemBase);
	}
	rect.setSize(sf::Vector2f(5.f, m_note->stemHeight));

	sf::RectangleShape connectorRect = sf::RectangleShape();
	sf::Vector2f connectorStart = stemBase;
	sf::Vector2f connectorEnd = connectorStart;
	
	
	float connectorLen = m_note->noteLength * 40;
	switch (m_note->stemType)
	{
	case Note::eStemType::none:
		break;
	case Note::eStemType::start:
		connectorEnd = connectorStart + sf::Vector2f(connectorLen, 0);
		break;
	case Note::eStemType::halfStart:
		connectorEnd = connectorStart + sf::Vector2f(connectorLen/2, 0);
		break;
	case Note::eStemType::end:
		connectorEnd = connectorStart - sf::Vector2f(connectorLen, 0);
		break;
	case Note::eStemType::halfEnd:
		connectorEnd = connectorStart - sf::Vector2f(connectorLen/2, 0);
		break;
	default:
		break;
	}

	connectorRect.setPosition(connectorStart);
	connectorRect.setSize(sf::Vector2f(connectorEnd.x - connectorStart.x, 5.f));

	sf::Color col = sf::Color(100, 50, 50);
	col.b = 255;
	rect.setFillColor(col);
	connectorRect.setFillColor(col);

	target->draw(rect);
	target->draw(connectorRect);
	if (m_note->noteLength == 1) {
		connectorRect.setPosition(connectorStart + sf::Vector2f(0, 10));
		target->draw(connectorRect);
	}
}

// TODO
void NoteRenderComponent::renderDot(sf::RenderTarget* target) {
	sf::CircleShape circ(GetEntity()->GetSize().x/7.f);

	sf::Vector2f noteSize = GetEntity()->GetSize();
	circ.setPosition(GetEntity()->GetPos() + sf::Vector2f(1.f * noteSize.x, noteSize.y * .2f));

	sf::Color col = sf::Color(100, 50, 250);
	col.b = 255;
	circ.setFillColor(col);

	target->draw(circ);
}
