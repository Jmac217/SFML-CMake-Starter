#include "pch.h"
#include "Player.h"

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		virtual ~Game();

		void update();
		void updatePlayer();
		void updateCollision();
		void render();
		void renderPlayer();

		const sf::RenderWindow& getWindow() const;

	private:
		sf::RenderWindow window;
		sf::Event e;

		Player* player;

		void initWindow();
		void initPlayer();
	};

}