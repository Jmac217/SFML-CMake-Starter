#include "Game.h"

namespace Mac {

	Game::Game()
	{
		this->initVariables();
		this->initWindow();
		this->initFont();
		this->initText();
	}

	Game::~Game()
	{
		delete this->window;
	}

	const bool& Game::getEndgame() const
	{
		return this->endGame;
	}

	const bool Game::running() const
	{
		return this->window->isOpen();
	}

	void Game::pollEvents()
	{
		while (this->window->pollEvent(this->sfEvent))
		{
			switch (this->sfEvent.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->sfEvent.key.code == sf::Keyboard::Escape)
					this->window->close();
				break;
			}
		}
	}

	void Game::update()
	{
		this->pollEvents();

		if (!this->endGame)
		{

			this->spawnBalls();

			this->updatePlayer();

			this->updateCollision();

			this->updateGui();

			
		}
	}

	void Game::render()
	{
		this->window->clear();

		this->player.render(this->window);

		for (auto i : this->balls)
		{
			i.render(this->window);
		}

		this->renderGui(this->window);

		if (this->endGame)
			this->window->draw(this->endGameText);

		this->window->display();
	}

	void Game::renderGui(sf::RenderTarget* target)
	{
		target->draw(guiText);
	}

	void Game::spawnBalls()
	{
		if (this->spawnTimer < this->spawnTimerMax)
			this->spawnTimer += 1.0f;
		else
		{
			if (this->balls.size() < this->maxBalls)
			{
				this->balls.push_back(Ball(*this->window, this->randomizeBallType()));

				this->spawnTimer = 0.0f;
			}
		}
	}

	const int Game::randomizeBallType() const
	{
		int type = BallTypes::DEFAULT;
		int randValue = rand() % 100 + 1;

		if (randValue > 80)
			type = BallTypes::DAMAGING;
		else if (randValue > 60 && randValue < 80)
			type = BallTypes::HEALING;

		return type;
	}

	void Game::updatePlayer()
	{
		this->player.update(this->window);

		if (this->player.getHP() <= 0)
			this->endGame = true;
	}

	void Game::updateCollision()
	{
		for (size_t i = 0; i < this->balls.size(); i++)
		{
			this->balls[i].update();
			if (this->player
				.getShape()
				.getGlobalBounds()
				.intersects(this->balls[i]
					.getShape()
					.getGlobalBounds()
				)
			)
			{
				switch (this->balls[i].getType())
				{
				case BallTypes::DEFAULT:
					this->points++;
					this->player.shape.setSize(sf::Vector2f(this->player.gainSize(1.0f), this->player.gainSize(1.0f)));
					break;
				case BallTypes::DAMAGING:
					this->player.takeDamage(1);
					break;
				case BallTypes::HEALING:
					this->player.gainHealth(1);
					break;
				}

				this->balls.erase(this->balls.begin() + i);
			}
			
		}
	}

	void Game::updateGui()
	{
		std::stringstream ss;
		ss	<< "Points: " << this->points
			<< "\n"
			<< "Health: " << this->player.getHP()
			<< " / " << this->player.getHPMax()
			<< std::endl;
		this->guiText.setString(ss.str());
	}

	void Game::initVariables()
	{
		this->endGame = false;
		this->spawnTimerMax = 50.0f;
		this->spawnTimer = this->spawnTimerMax;
		this->maxBalls = 20;
		this->points = 0;
	}

	void Game::initWindow()
	{
		this->videoMode = sf::VideoMode(800, 600);
		this->window = new sf::RenderWindow(this->videoMode, "SFML: Game 2", sf::Style::Close | sf::Style::Titlebar);
		this->window->setFramerateLimit(60);
	}

	void Game::initFont()
	{
		if (!this->font.loadFromFile("Fonts/FiraCode-Retina.ttf"))
		{
			std::cout << "Font didn't load" << std::endl;
		}
	}

	void Game::initText()
	{
		this->guiText.setFont(this->font);
		this->guiText.setFillColor(sf::Color::White);
		this->guiText.setCharacterSize(24);
		this->guiText.setString("Points: 0");

		this->endGameText.setFont(this->font);
		this->endGameText.setFillColor(sf::Color::Red);
		this->endGameText.setCharacterSize(60);
		this->endGameText.setPosition(sf::Vector2f(100, 300));
		this->endGameText.setString("GAME OVER");
	}

}