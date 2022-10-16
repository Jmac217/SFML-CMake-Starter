#pragma once
#include "Character.h"

namespace Mac {

	struct Enemy
		: public Character
	{
		Enemy(EntityManager* l_entityManager);
		~Enemy() = default;

		void OnEntityCollision(EntityBase* l_collider, bool l_attack);
		void Update(float l_deltaTime);
	private:
		sf::Vector2f m_destination;
		bool m_hasDestination;
	};
}