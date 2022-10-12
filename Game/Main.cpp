#include "pch.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML");

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

		// DRAW HERE

		window.display();
	}
}