#pragma once

#include <SFML/Graphics.hpp>

namespace Mac {

	struct Enemy
	{
		Enemy(float X_Pos, float Y_Pos);
		virtual ~Enemy() = default;

		const sf::FloatRect getBounds() const;
		const int& getPoints() const;
		const int& getDamage() const;

		void update();
		void render(sf::RenderTarget* target);

	private:
		sf::CircleShape shape;
		int type;
		int hp;
		int hpMax;
		int damage;
		int points;
		
		unsigned int complexity;

		float speed;

		void initVariables();
		void initShape();
	};
}