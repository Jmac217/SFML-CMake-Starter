#pragma once

#include "EntityBase.h"
#include "SpriteSheet.h"

namespace Mac {

	struct Character
		: public EntityBase
	{
		Character(EntityManager* l_entityManager);
		virtual ~Character() = default;

		void Move(const Direction& l_dir);

		void Jump();
		void Attack();
		void GetHurt(const int& l_damage);

		void Load(const std::string& l_path);

		virtual void OnEntityCollision(EntityBase* l_collider, bool l_attack) = 0;

		virtual void Update(float l_deltaTime);

		void Draw(sf::RenderWindow* l_window);
	protected:
		void UpdateAttackAABB();
		void Animate();
		SpriteSheet m_spriteSheet;
		float m_jumpVelocity;
		int m_hitpoints;
		sf::FloatRect m_attackAABB;
		sf::Vector2f m_attackAABBoffset;
	private:
		friend class EntityManager;
	};
}