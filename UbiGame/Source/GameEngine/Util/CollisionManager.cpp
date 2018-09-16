#include "CollisionManager.h"


#include "GameEngine/EntitySystem/Components/CollidableComponent.h"

#include <assert.h>

using namespace GameEngine;


CollisionManager* CollisionManager::sm_instance = nullptr;

CollisionManager::CollisionManager()
{

}


CollisionManager::~CollisionManager()
{

}


void CollisionManager::RegisterCollidable(CollidableComponent* collidable)
{
	auto found = std::find(m_collidables.begin(), m_collidables.end(), collidable);
	assert(found == m_collidables.end()); //Drop an assert if we add duplicate;
	if (found == m_collidables.end())
	{
		m_collidables.push_back(collidable);
		m_colCompToCollidedComponents[collidable] = std::vector<CollidableComponent*>();
	}
}


void CollisionManager::UnRegisterCollidable(CollidableComponent* collidable)
{
	auto found = std::find(m_collidables.begin(), m_collidables.end(), collidable);
	assert(found != m_collidables.end()); //Drop an assert if we remove a non existing entity;

	if (found != m_collidables.end())
	{
		m_collidables.erase(found);
		m_colCompToCollidedComponents.erase(*found);
	}
}