#pragma once
#include "GameEngine/EntitySystem/Components/RenderComponent.h"

namespace GameEngine {
	class NoteRenderComponent : public RenderComponent {
	public:
		enum eStemType { none, start, middle, end };
		enum eNoteLength { whole, half, quarter, eighth, sixteenth };

		void Render(sf::RenderTarget* target);
		void setNoteProps(eStemType eStemType, int stemHeight, bool stemUp, bool isDotted, bool isRest);

		eNoteLength getNoteLength() { return m_noteLength; }
		eStemType getStemType() { return m_stemType; }
		bool getIsStemUp() { return m_isStemUp; }
		bool getIsDotted() { return m_isDotted; }
		bool getIsRest() { return m_isRest; }
		int getStemHeight() { return m_stemHeight; }

	private:
		eNoteLength m_noteLength;
		eStemType m_stemType;
		int m_stemHeight;
		bool m_isStemUp;
		bool m_isDotted;
		bool m_isRest;

		void renderNote(sf::RenderTarget* target);
		void renderStem(sf::RenderTarget* target);
		void renderRest(sf::RenderTarget* target);
		void renderDot(sf::RenderTarget* target);
	};
}