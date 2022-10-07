#include <iostream>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#pragma once

namespace Mac {

	// Wrapper Class for "Game Engine"

	struct Game
	{
		// Constructors and Destructors
		Game();
		virtual ~Game();

		const bool Running() const;
		const bool EndGame() const;

		// Member Functions
		void update();
		void render();
		void pollEvents();
		void updateMousePositions();

	private:
		sf::RenderWindow* window;
		sf::VideoMode videoMode;
		sf::Event ev;

		sf::Vector2i mousePosWindow;
		sf::Vector2f mousePosView;

		sf::Font font;
		sf::Text uiText;

		unsigned int points;
		int health;
		float enemySpawnTimer;
		float enemySpawnTimerMax;
		int maxEnemies;
		bool mouseHeld;
		bool endGame;

		sf::RectangleShape enemy;
		std::vector<sf::RectangleShape> Enemies;
	private:
		// Private Member Functions
		void initVariables();
		void initWindow();
		void initEnemies();
		void initFonts();
		void initText();
		void spawnEnemy();
		void updateEnemies();
		void renderEnemies(sf::RenderTarget& target);
		void renderText(sf::RenderTarget& target);
		void updateText();
	};

}