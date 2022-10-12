#include "pch.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Bounce");

	sf::Texture bouncyBallTexture;
	bouncyBallTexture.loadFromFile("Textures/Ball.png");

	sf::Vector2u size = bouncyBallTexture.getSize();

	sf::Sprite bouncyBallSprite(bouncyBallTexture);

	bouncyBallSprite.setOrigin(size.x / 2, size.y / 2);
	sf::Vector2f increment(0.4f, 0.4f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		if ((bouncyBallSprite.getPosition().x + (size.x / 2) > window.getSize().x && increment.x > 0)
			|| (bouncyBallSprite.getPosition().x - (size.x / 2) < 0 && increment.x < 0))
		{
			increment.x = -increment.x;
		}

		if ((bouncyBallSprite.getPosition().y + (size.y / 2) > window.getSize().y && increment.y > 0)
			|| (bouncyBallSprite.getPosition().y - (size.y / 2) < 0 && increment.y < 0))
		{
			increment.y = -increment.y;
		}

		bouncyBallSprite.setPosition(bouncyBallSprite.getPosition() + increment);

		window.clear(sf::Color::Yellow);
		// Draw Here ===================

		window.draw(bouncyBallSprite);

		//==============================
		window.display();
	}
}