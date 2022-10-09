#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <map>

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

namespace Mac {

	struct Game
	{
		Game();
		virtual ~Game();

		void Run();

		void UpdatePollEvents();
		void UpdateInput();
		void UpdateGUI();
		void UpdateBullets();
		void UpdateEnemies();
		void UpdateCombat();
		void UpdateWorld();
		void UpdateCollision();
		void Update();
		void RenderGUI();
		void RenderWorld();
		void Render();

	private:
		void initWindow();
		void initTextures();
		void initWorld();
		void initSystems();
		void initPlayer();
		void initEnemies();
		void initGUI();

		sf::RenderWindow* window;

		sf::Font font;
		sf::Text pointText;

		sf::Text GameOverText;

		sf::Sprite WorldSprite;
		sf::Texture WorldTexture;

		sf::RectangleShape PlayerHPBar;
		sf::RectangleShape PlayerHPBarBack;

		std::map<std::string, sf::Texture*> textures;
		std::vector<Bullet*> bullets;

		unsigned int points;

		Player* player;
		Enemy* enemy;

		float spawnTimer;
		float spawnTimerMax;
		std::vector<Enemy*> enemies;
	};

}