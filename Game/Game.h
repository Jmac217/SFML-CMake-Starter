#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>

#include "Player.h"
#include "Ball.h"

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		virtual ~Game();

		const bool& getEndgame() const;

		const bool running() const;
		void pollEvents();

		void update();
		void render();
		void renderGui(sf::RenderTarget* target);
		void spawnBalls();
		const int randomizeBallType() const;
		void updatePlayer();
		void updateCollision();
		void updateGui();

	private:
		sf::VideoMode videoMode;
		sf::RenderWindow* window;
		sf::Event sfEvent;
		sf::Font font;
		sf::Text guiText;
		sf::Text endGameText;

		std::vector<Ball> balls;

		Player player;

		bool endGame;

		int points;
		int maxBalls;

		float spawnTimerMax;
		float spawnTimer;

		void initVariables();
		void initWindow();
		void initFont();
		void initText();
	};

}