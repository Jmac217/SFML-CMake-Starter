#include "pch.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");

	sf::RectangleShape rectangle(sf::Vector2f(128.0f, 128.0f));

	rectangle.setFillColor(sf::Color::Cyan);
	rectangle.setPosition(320, 240);
	rectangle.setOrigin(
		rectangle.getSize().x / 2, 
		rectangle.getSize().y / 2
	);

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
		window.clear(sf::Color::Yellow);
		// Draw Here ===================

		window.draw(rectangle);

		//==============================
		window.display();
	}
}