#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>

#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		virtual ~Game();

		void Run();
		void Update();
		void Render();

	private:
		void initWindow();

		sf::RenderWindow* window;
	};

}