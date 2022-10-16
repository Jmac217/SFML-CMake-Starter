#include "pch.h"

#include "EntityManager.h"
#include "SharedContext.h"

namespace Mac {


	EntityManager::EntityManager(
			SharedContext* l_context
		,	unsigned l_maxEntities
	)
		:	m_context(l_context)
		,	m_maxEntities(l_maxEntities)
		,	m_idCounter(0)
	{
		LoadEnemyTypes("EnemyList.list");
		RegisterEntity<Player>(EntityType::Player);
		RegisterEntity<Enemy>(EntityType::Enemy);
	}

	EntityManager::~EntityManager()
	{
		Purge();
	}

	int EntityManager::Add(const EntityType& l_type, const std::string& l_name /*= ""*/)
	{
		auto i = m_entityFactory.find(l_type);

		if (i == m_entityFactory.end())
			return -1;

		EntityBase* entity = i->second();
		entity->m_ID = m_idCounter;

		if (l_name != "")
			entity->m_name = l_name;

		m_entities.emplace(m_idCounter, entity);

		if (l_type == EntityType::Enemy)
		{
			auto j = m_enemyTypes.find(l_name);
			if (j != m_enemyTypes.end())
			{
				Enemy* enemy = (Enemy*)entity;
				enemy->Load(j->second);
			}
		}

		++m_idCounter;
		return m_idCounter - 1;
	}

	Mac::EntityBase* EntityManager::Find(unsigned l_ID)
	{
		auto i = m_entities.find(l_ID);

		if (i == m_entities.end())
			return nullptr;

		return i->second;
	}

	Mac::EntityBase* EntityManager::Find(const std::string& l_name)
	{
		for (auto& i : m_entities)
			if (i.second->GetName() == l_name)
				return i.second;

		return nullptr;
	}

	void EntityManager::Remove(unsigned l_ID)
	{
		m_entitiesToRemove.emplace_back(l_ID);
	}

	void EntityManager::Update(float l_deltaTime)
	{
		for (auto& i : m_entities)
			i.second->Update(l_deltaTime);

		EntityCollisionCheck();
		ProcessRemovals();
	}

	void EntityManager::Draw()
	{
		sf::RenderWindow* win = m_context->m_window->GetRenderWindow();
		sf::FloatRect viewSpace = m_context->m_window->GetViewSpace();

		for (auto& i : m_entities)
		{
			if (!viewSpace.intersects(i.second->m_AABB))
				continue;

			i.second->Draw(win);
		}
	}

	void EntityManager::Purge()
	{
		for (auto& i : m_entities)
			delete i.second;

		m_entities.clear();
		m_idCounter = 0;
	}

	Mac::SharedContext* EntityManager::GetContext()
	{
		return m_context;
	}

	void EntityManager::ProcessRemovals()
	{
		while (m_entitiesToRemove.begin() != m_entitiesToRemove.end())
		{
			unsigned id = m_entitiesToRemove.back();
			auto i = m_entities.find(id);

			if (i != m_entities.end())
			{
				std::cout << "Discarding Entity: " << i->second->GetID() << std::endl;
				delete i->second;
				m_entities.erase(i);
			}

			m_entitiesToRemove.pop_back();
		}
	}

	void EntityManager::LoadEnemyTypes(const std::string& l_name)
	{

		std::ifstream file;

		file.open(Utils::GetResourceDirectory() + std::string("Media/Characters/") + l_name);

		if (!file.is_open())
		{
			std::cout << "! Failed loading file: " << l_name << std::endl;
			return;
		}

		std::string line;

		while (std::getline(file, line))
		{
			if (line[0] == '|')
				continue;

			std::stringstream keystream(line);

			std::string name;
			std::string charFile;

			keystream >> name >> charFile;

			m_enemyTypes.emplace(name, charFile);
		}

		file.close();
		
	}

	void EntityManager::EntityCollisionCheck()
	{
		if (m_entities.empty())
			return;

		for (
			auto i = m_entities.begin();
			std::next(i) != m_entities.end();
			++i
			)
			for (
				auto j = std::next(i);
				j != m_entities.end();
				++j
				)
			{
				if (i->first == j->first)
					continue;

				// Regular AABB bounding box collision.
				if (i->second->m_AABB.intersects(j->second->m_AABB))
				{
					i->second->OnEntityCollision(j->second, false);
					j->second->OnEntityCollision(i->second, false);
				}

				EntityType type1 = i->second->GetType();
				EntityType type2 = j->second->GetType();

				if (type1 == EntityType::Player || type1 == EntityType::Enemy)
				{
					Character* c1 = (Character*)i->second;

					if (c1->m_attackAABB.intersects(j->second->m_AABB))
						c1->OnEntityCollision(j->second, true);
				}

				if (type2 == EntityType::Player || type2 == EntityType::Enemy)
				{
					Character* c2 = (Character*)j->second;

					if (c2->m_attackAABB.intersects(i->second->m_AABB))
						c2->OnEntityCollision(i->second, true);
				}

			}
	}

}