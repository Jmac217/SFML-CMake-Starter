#pragma once

#include "Character.h"
#include "EventManager.h"

namespace Mac {

	struct Player
		: public Character
	{
		Player(EntityManager* l_entityManager);
		~Player();

		void OnEntityCollision(EntityBase* l_collider, bool l_attack);
		void React(EventDetails* l_details);
	};
}