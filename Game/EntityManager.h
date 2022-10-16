#pragma once

#include "Player.h"
#include "Enemy.h"

namespace Mac {

	using EntityContainer = std::unordered_map<unsigned, EntityBase*>;
	using EntityFactory = std::unordered_map<EntityType, std::function<EntityBase* (void)>>;
	using EnemyTypes = std::unordered_map<std::string, std::string>;

	// Forward Declaration
	struct SharedContext;

	struct EntityManager
	{
		EntityManager(SharedContext* l_context, unsigned l_maxEntities);
		~EntityManager();

		int Add(const EntityType& l_type, const std::string& l_name = "");
		EntityBase* Find(unsigned l_ID);
		EntityBase* Find(const std::string& l_name);
		void Remove(unsigned l_ID);

		void Update(float l_deltaTime);
		void Draw();

		void Purge();

		SharedContext* GetContext();
	private:
		template<typename T>
		void RegisterEntity(const EntityType& l_type)
		{
			m_entityFactory[l_type] = [this]() -> EntityBase*
			{
				return new T(this);
			};
		}

		void ProcessRemovals();
		void LoadEnemyTypes(const std::string& l_name);
		void EntityCollisionCheck();

		EntityContainer m_entities;
		EnemyTypes m_enemyTypes;
		EntityFactory m_entityFactory;
		SharedContext* m_context;
		unsigned m_idCounter;
		unsigned m_maxEntities;

		std::vector<unsigned> m_entitiesToRemove;
	};

}