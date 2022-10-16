#pragma once

#include "Bitmask.h"
#include "EntityManager.h"
#include "Event_Queue.h"
#include "EntityEvents.h"
#include "Observer.h"
#include "ECS_Types.h"

namespace Mac {

	using EntityList = std::vector<EntityId>;

	using Requirements = std::vector<Bitmask>;


	struct SystemManager;

	struct S_Base
		: public Observer 
	{
		S_Base(const System& l_id, SystemManager* l_systemMgr);
		virtual ~S_Base();

		bool AddEntity(const EntityId& l_entity);
		bool HasEntity(const EntityId& l_entity);
		bool RemoveEntity(const EntityId& l_entity);
		System GetId();
		bool FitsRequirements(const Bitmask& l_bits);
		void Purge();
		virtual void Update(float l_deltaTime) = 0;
		virtual void HandleEvent(const EntityId& l_entity, const EntityEvent& l_event) = 0;
	protected:
		System m_id;
		Requirements m_requiredComponents;
		EntityList m_entities;
		SystemManager* m_systemManager;
	};

}