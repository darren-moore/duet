#pragma once
#include <vector>
#include <unordered_map>

namespace GameEngine
{
	class CollidableComponent;

	class CollisionManager
	{
	public:		
		~CollisionManager();

		static CollisionManager* GetInstance() { if (!sm_instance) sm_instance = new CollisionManager(); return sm_instance; }

		void RegisterCollidable(CollidableComponent* collidable);
		void UnRegisterCollidable(CollidableComponent* collidable);
		//TODO - optimisation - instead of getcollidables, provide get near collidables so that we do not check collisions with all entities, just the ones that could potentially collide
		std::vector<CollidableComponent*>& GetCollidables() { return m_collidables; }
		std::vector<CollidableComponent*>& GetCollidedComponents(CollidableComponent* component) { return m_colCompToCollidedComponents[component]; }

	private:
		CollisionManager();
		static CollisionManager* sm_instance;
		std::unordered_map<CollidableComponent*, std::vector<CollidableComponent*>> m_colCompToCollidedComponents;
		std::vector<CollidableComponent*> m_collidables;

	};
}


