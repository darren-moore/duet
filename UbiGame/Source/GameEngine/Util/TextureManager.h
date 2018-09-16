#pragma once
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

namespace GameEngine
{
	//TODO - if needed, move out of Engine part to some sort of loader on the game side of things
	namespace eTexture
	{
		enum type
		{
			None = -1,
			Note = 0,
			Highlight,
			BG,
			TapParticle,
			MissParticle,
			QuarterRest,
			Cloud,
			Count
		};
	}	

	inline const char* GetPath(eTexture::type texture)
	{
		switch (texture)
		{
		case eTexture::Note:		return "note.png";
		case eTexture::Highlight:	return "highlight.png";
		case eTexture::BG:			return "bg.png";
		case eTexture::TapParticle: return "TapParticle.png";
		case eTexture::MissParticle:return "MissParticle.png";
		case eTexture::QuarterRest:		return "QuarterRest.png";
		case eTexture::Cloud:		return "cloud.png";
		default:       return "UnknownTexType";
		}
	}

	class TextureManager
	{
	public:
		static TextureManager* GetInstance() { if (!sm_instance) sm_instance = new TextureManager(); return sm_instance; }
		~TextureManager();

		void LoadTextures();
		void UnLoadTextures();

		sf::Texture* GetTexture(eTexture::type texture) const { return m_textures[(int)texture]; }

	private:
		TextureManager();
		static TextureManager* sm_instance;

		sf::Texture* m_textures[eTexture::Count];
	};
}

namespace TextureHelper
{
	static sf::Vector2f GetTextureTileSize(GameEngine::eTexture::type texture)
	{
		switch (texture)
		{
		case GameEngine::eTexture::Note:		return sf::Vector2f(32.f, 32.f);
		case GameEngine::eTexture::Highlight:	return sf::Vector2f(640.f, 180.f);
		case GameEngine::eTexture::BG:			return sf::Vector2f(1280.f, 720.f);
		case GameEngine::eTexture::TapParticle:	return sf::Vector2f(1280.f, 720.f);
		case GameEngine::eTexture::MissParticle:return sf::Vector2f(1280.f, 720.f);
		case GameEngine::eTexture::QuarterRest:		return sf::Vector2f(233.f, 330.f);
		case GameEngine::eTexture::Cloud:		return sf::Vector2f(1500.f, 720.f);
		default:								return sf::Vector2f(-1.f, -1.f);
		}
	}
}
