#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
namespace Mac {

	struct Player
	{
		Player(float x = 0.0f, float y = 0.0f);
		~Player();

		const sf::RectangleShape& getShape() const;
		sf::RectangleShape shape;

		void update(const sf::RenderTarget* target);
		void render(sf::RenderTarget* target);
		void updateInput();
		void updateWindowBoundsCollission(const sf::RenderTarget* target);

		const int& getHP() const;
		const int& getHPMax() const;

		void takeDamage(const int damage);
		void gainHealth(const int health);
		float gainSize(float size);
	private:

		int hp;
		int hpMax;
		float movementSpeed;
		float size;

		void initVariables();
		void initShape();
	};
}

