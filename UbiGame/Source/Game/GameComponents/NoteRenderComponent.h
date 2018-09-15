/*
Renders a sprite along with other visuals of a musical note. 
*/

#pragma once
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include "../Util/Note.h"

namespace Game {
	class NoteRenderComponent : public GameEngine::SpriteRenderComponent {
	public:

		void Render(sf::RenderTarget* target);
		void setNote(Note* note) { m_note = note; }

		Note* getNote() { return m_note; }

	private:
		Note* m_note;
		float m_stemHeight = 75.f;

		void renderStem(sf::RenderTarget* target);
		void renderRest(sf::RenderTarget* target);
		void renderDot(sf::RenderTarget* target);
	};
}