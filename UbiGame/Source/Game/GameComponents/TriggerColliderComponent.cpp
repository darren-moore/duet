#include "TriggerColliderComponent.h"

#include <vector>
#include "GameEngine/Util/CollisionManager.h"
#include "GameEngine/EntitySystem/Entity.h"

using namespace GameEngine;

void Game::TriggerColliderComponent::Update()
{
	//For the time being just a simple intersection check that moves the entity out of all potential intersect boxes
	std::vector<CollidableComponent*>& collidables = CollisionManager::GetInstance()->GetCollidables();

	bool collisionFound = false;
	int collidedComponent = 0;

	for (int a = 0; a < collidables.size(); ++a)
	{
		CollidableComponent* colComponent = collidables[a];
		if (colComponent == this)
			continue;

		AABBRect intersection;
		AABBRect myBox = GetWorldAABB();
		AABBRect colideBox = colComponent->GetWorldAABB();
		if (myBox.intersects(colideBox, intersection)) {
			collisionFound = true;
			collidedComponent = a;
		}
	}

	// collidables[collidedComponent]->GetEntity();
}