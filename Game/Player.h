#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "Bullet.h"

namespace Mac {
	struct Player
	{
		Player();
		virtual ~Player() = default;

		const sf::Vector2f& getPos() const;
		const sf::FloatRect getBounds() const;
		const int& getHP() const;
		const int& getHPMax() const;

		void setPosition(sf::Vector2f pos);
		void setPosition(float X, float Y);
		void setHP(const int HP);
		void loseHP(const int HP);

		void Move(const float X, const float Y);
		const bool canAttack();

		void Update();
		void updateAttack();
		void Render(sf::RenderTarget& target);
	private:
		sf::Texture texture;
		sf::Sprite	sprite;

		float Speed = 10.0f;

		int hp;
		int hpMax;

		float attackCooldown;
		float attackCooldownMax;

		void initVariables();
		void initTexture();
		void initSprite();
	};
}