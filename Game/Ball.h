#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

namespace Mac {

	enum BallTypes {DEFAULT =0, DAMAGING, HEALING, TYPES};

	struct Ball
	{
		Ball(const sf::RenderWindow& window, int type);
		virtual ~Ball();

		const sf::CircleShape getShape() const;

		void update();
		void render(sf::RenderTarget* target);

		const int& getType() const;

	private:
		sf::CircleShape shape;
		int type;

		void initShape(const sf::RenderWindow& window);
	};
}