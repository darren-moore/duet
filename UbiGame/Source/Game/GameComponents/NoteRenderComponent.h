#pragma once
#include "GameEngine/EntitySystem/Components/RenderComponent.h"
#include "Game/Util/Note.h"

namespace GameEngine {
	class NoteRenderComponent : public RenderComponent {
	public:
		enum eStemType { none, start, middle, end };
		enum eNoteLength { whole, half, quarter, eighth, sixteenth };

		void Render(sf::RenderTarget* target);
		void setNote(Note* note) { m_note = note; }

		Note* getNote() { return m_note; }

	private:
		Note* m_note;
		int m_stemHeight = 100;

		void renderNote(sf::RenderTarget* target);
		void renderStem(sf::RenderTarget* target);
		void renderRest(sf::RenderTarget* target);
		void renderDot(sf::RenderTarget* target);
	};
}