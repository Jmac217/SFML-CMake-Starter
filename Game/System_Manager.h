#pragma once

#include "Window.h"
#include "S_Renderer.h"
//#include "S_Movement.h"
//#include "S_Collision.h"
//#include "S_Control.h"
//#include "S_State.h"
//#include "S_SheetAnimation.h"
#include "Event_Queue.h"
#include "MessageHandler.h"
#include "DebugOverlay.h"

namespace Mac {

	using SystemContainer = std::unordered_map<System, S_Base*>;
	using EntityEventContainer = std::unordered_map<EntityId, EventQueue>;

	// Forward Declaration
	struct EntityManager;

	struct SystemManager
	{

		SystemManager();
		~SystemManager();

		void SetEntityManager(EntityManager* l_entityMgr);
		EntityManager* GetEntityManager();
		MessageHandler* GetMessageHandler();

		template<class T>
		T* GetSystem(const System& l_system) {
			auto itr = m_systems.find(l_system);
			return(
				itr != m_systems.end()
				? dynamic_cast<T*>(itr->second)
				: nullptr
			);
		}

		void AddEvent(const EntityId& l_entity, const EventID& l_event);
		void Update(float l_deltaTime);
		void HandleEvents();
		void Draw(Window* l_wind, unsigned int l_elevation);
		void EntityModified(const EntityId& l_entity, const Bitmask& l_bits);
		void RemoveEntity(const EntityId& l_entity);
		void PurgeEntities();
		void PurgeSystems();
		DebugOverlay* m_debugOverlay;

	private:
		SystemContainer m_systems;
		EntityManager* m_entityManager;
		EntityEventContainer m_events;
		MessageHandler m_messages;
	};

}