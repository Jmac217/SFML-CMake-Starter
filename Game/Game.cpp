#include "Game.h"

namespace Mac {

	Game::Game()
	{
		this->initWindow();
	}

	Game::~Game()
	{
		delete this->window;
	}

	void Game::Run()
	{
		while (this->window->isOpen())
		{
			this->Update();
			this->Render();
		}
	}

	void Game::Update()
	{
		// Poll Events
	}

	void Game::Render()
	{	
		// Begin Loop
		this->window->clear();
		// -------------------

		// GAME LOOP HERE

		// -------------------
		this->window->display();
		// End Loop
	}

	void Game::initWindow()
	{
		this->window = new sf::RenderWindow(
			sf::VideoMode(800, 600)
			, "SFML - Space Shooter"
			, sf::Style::Close | sf::Style::Titlebar);
	}

}