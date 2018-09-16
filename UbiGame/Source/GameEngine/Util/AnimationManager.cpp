#include "AnimationManager.h"


using namespace GameEngine;

AnimationManager* AnimationManager::sm_instance = nullptr;

AnimationManager::AnimationManager()
{

}


AnimationManager::~AnimationManager()
{

}


void AnimationManager::InitStaticGameAnimations()
{
	/*
	m_animDefinitions.push_back
	(
		SAnimationDefinition(
			EAnimationId::Smoke,
			eTexture::Particles,
			sf::Vector2i(0, 0),
			10,
			15)
	);
	*/

	m_animDefinitions.push_back(
		SAnimationDefinition(
			EAnimationId::FillHit,
			eTexture::TapParticle,
			sf::Vector2i(0, 0),
			3,
			24)
	);

	m_animDefinitions.push_back(
		SAnimationDefinition(
			EAnimationId::FillMiss,
			eTexture::MissParticle,
			sf::Vector2i(0, 0),
			3,
			24)
	);

	m_animDefinitions.push_back(
		SAnimationDefinition(
			EAnimationId::Metronome,
			eTexture::Metronome,
			sf::Vector2i(0, 0),
			2,
			2
		)
	);
}


void AnimationManager::ReleaseStaticGameAnimations()
{
	m_animDefinitions.clear();
}


const SAnimationDefinition* AnimationManager::GetAnimDefinition(EAnimationId::type animId) const
{
	for (int a = 0; a < m_animDefinitions.size(); ++a)
	{
		if (m_animDefinitions[a].m_animId == animId)
			return &m_animDefinitions[a];
	}

	return nullptr;
}
