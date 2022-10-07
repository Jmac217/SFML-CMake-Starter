#include "Game.h"

namespace Mac {

	Game::Game()
	{
		this->initVariables();
		this->initWindow();
		this->initFonts();
		this->initText();
		this->initEnemies();
	}

	Game::~Game()
	{
		delete this->window;
	}

	const bool Game::Running() const
	{
		return this->window->isOpen();
	}

	const bool Game::EndGame() const
	{
		return this->endGame;
	}

	void Game::update()
	{
		this->pollEvents();

		if (!this->endGame)
		{
			this->updateMousePositions();

			this->updateText();

			this->updateEnemies();
		}

		if (this->health <= 0)
			this->endGame = true;
	}

	void Game::render()
	{
		this->window->clear();

		// draw game objects here
		this->renderEnemies(*this->window);

		this->renderText(*this->window);

		this->window->display();
	}

	void Game::pollEvents()
	{
		while (this->window->pollEvent(this->ev))
		{
			switch (this->ev.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (ev.key.code == sf::Keyboard::Escape)
					this->window->close();
					break;
			}
		}
	}

	void Game::updateMousePositions()
	{
		this->mousePosWindow = sf::Mouse::getPosition(*this->window);
		this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
	}

	void Game::initVariables()
	{
		this->window = nullptr;
		this->points = 0;
		this->health = 10;
		this->enemySpawnTimerMax = 10.0f;
		this->enemySpawnTimer = this->enemySpawnTimerMax;
		this->maxEnemies = 15;
		this->mouseHeld = false;
		this->endGame = false;
	}

	void Game::initWindow()
	{
		this->videoMode.height = 600;
		this->videoMode.width = 800;

		this->window = new sf::RenderWindow(this->videoMode
											, "SFML"
											, sf::Style::Titlebar
											| sf::Style::Close
		);
		this->window->setFramerateLimit(60);
	}

	void Game::initEnemies()
	{
		this->enemy.setPosition(10.0f, 10.0f);
		this->enemy.setSize(sf::Vector2f(100.f, 100.f));
		this->enemy.setScale(sf::Vector2f(1.5f, 1.5f));
		//this->enemy.setFillColor(sf::Color(130, 180, 200, 255));
		//this->enemy.setOutlineColor(sf::Color::Blue);
		//this->enemy.setOutlineThickness(5.0f);
	}

	void Game::initFonts()
	{
		if (!this->font.loadFromFile("Fonts/FiraCode-Regular.ttf"))
		{
			std::cout << "Error\n";
		}
	}

	void Game::initText()
	{
		this->uiText.setFont(this->font);
		this->uiText.setCharacterSize(48);
		this->uiText.setFillColor(sf::Color::White);
		//this->uiText.setOutlineThickness(0.5f);
		//this->uiText.setOutlineColor(sf::Color::Black);
		this->uiText.setString("Points: 0");
		
	}

	void Game::spawnEnemy()
	{
		this->enemy.setPosition(
			static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x))
			, 0.0f
		);

		int type = rand() % 5;

		switch (type)
		{
		case 0:
			this->enemy.setSize(sf::Vector2f(10.0f, 10.0f));
			this->enemy.setFillColor(sf::Color::Red);
			break;
		case 1:
			this->enemy.setSize(sf::Vector2f(30.0f, 30.0f));
			this->enemy.setFillColor(sf::Color::Cyan);
			break;
		case 2:
			this->enemy.setSize(sf::Vector2f(10.0f, 10.0f));
			this->enemy.setFillColor(sf::Color::White);
			break;
		case 3:
			this->enemy.setSize(sf::Vector2f(5.0f, 5.0f));
			this->enemy.setFillColor(sf::Color::Blue);
			break;
		case 4:
			this->enemy.setSize(sf::Vector2f(7.0f, 7.0f));
			this->enemy.setFillColor(sf::Color::Yellow);
			break;
		default:break;
		}

		//this->enemy.setFillColor(sf::Color(130, 180, 200, 255));

		this->Enemies.push_back(this->enemy);
	}

	void Game::updateEnemies()
	{
		if (this->Enemies.size() < this->maxEnemies)
		{
			if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
			{
				this->spawnEnemy();
				this->enemySpawnTimer = 0.0f;
			}
			else
				this->enemySpawnTimer += 1.0f;
		}

		for (int i = 0; i < this->Enemies.size(); i++)
		{
			this->Enemies[i].move(0.0f, 1.0f);

			if (this->Enemies[i].getPosition().y > this->window->getSize().y)
			{
				this->Enemies.erase(this->Enemies.begin() + i);
				this->health -= 1;
				std::cout << "Health: " << this->health << std::endl;
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (!this->mouseHeld)
			{
				this->mouseHeld = true;
				bool deleted = false;

				for (size_t i = 0; i < this->Enemies.size() && deleted == false; i++)
				{
					if (this->Enemies[i].getGlobalBounds().contains(this->mousePosView))
					{
						deleted = true;
						this->Enemies.erase(this->Enemies.begin() + i);
						this->points += 10;
						std::cout << "Points: " << this->points << std::endl;
					}
				}
			}
		}
		else
		{
			this->mouseHeld = false;
		}
	}

	void Game::renderEnemies(sf::RenderTarget& target)
	{
		for (auto& e : this->Enemies)
		{
			this->window->draw(e);
		}
	}

	void Game::renderText(sf::RenderTarget& target)
	{
		target.draw(this->uiText);
	}

	void Game::updateText()
	{
		std::stringstream ss;

		ss	<< "Points: " << this->points
			<< "\n"
			<< "Health: " << this->health
			<< std::endl;


		this->uiText.setString(ss.str());
	}

}