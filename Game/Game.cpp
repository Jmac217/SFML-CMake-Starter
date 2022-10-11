#include "pch.h"
#include "Game.h"

namespace Mac {

	Game::Game()
	{
		this->initWindow();
		this->initPlayer();
	}

	Game::~Game()
	{
		delete this->player;
	}

	const sf::RenderWindow& Game::getWindow() const
	{
		return this->window;
	}

	void Game::update()
	{
		//Polling window events
		while (this->window.pollEvent(this->e))
		{
			if (this->e.type == sf::Event::Closed)
				this->window.close();
			else if (this->e.type == sf::Event::KeyPressed && this->e.key.code == sf::Keyboard::Escape)
				this->window.close();

			if (
				this->e.type == sf::Event::KeyReleased &&
				(
					this->e.key.code == sf::Keyboard::A ||
					this->e.key.code == sf::Keyboard::D ||
					this->e.key.code == sf::Keyboard::W ||
					this->e.key.code == sf::Keyboard::S
					)
				)
			{
				this->player->resetAnimationTimer();
			}
		}

		this->updatePlayer();

		this->updateCollision();
	}

	void Game::updatePlayer()
	{
		this->player->update();
	}

	void Game::updateCollision()
	{
		//Collision bottom of screen
		if (this->player->getPosition().y + this->player->getGlobalBounds().height > this->window.getSize().y)
		{
			this->player->canJump();
			this->player->resetVelocityY();
			this->player->setPosition(
				this->player->getPosition().x,
				this->window.getSize().y - this->player->getGlobalBounds().height
			);
		}
	}

	void Game::render()
	{
		this->window.clear(sf::Color(50, 50, 75, 255));
		// Draw Here=========

		this->renderPlayer();

		// ==================
		this->window.display();
	}

	void Game::renderPlayer()
	{
		this->player->render(this->window);
	}

	void Game::initWindow()
	{
		this->window.create(sf::VideoMode(800, 600), "Platformer", sf::Style::Close | sf::Style::Titlebar);
		this->window.setFramerateLimit(60);
	}

	void Game::initPlayer()
	{
		this->player = new Player;
	}

}