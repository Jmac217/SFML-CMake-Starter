#pragma once
#include "Snake.h"

namespace Mac {

	struct World
	{
		World(sf::Vector2u l_windSize);
		~World() = default;

		int GetBlockSize();

		void RespawnApple();

		void Update(Snake& l_player);
		void Render(sf::RenderWindow& l_window);
	private:
		sf::Vector2u m_windowSize;
		sf::Vector2i m_item;

		sf::CircleShape m_appleShape;
		sf::RectangleShape m_bounds[4];

		int m_blockSize;
	};
}