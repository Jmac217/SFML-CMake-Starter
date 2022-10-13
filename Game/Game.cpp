#include "pch.h"
#include "Game.h"

namespace Mac {

	Game::Game()
	{
		m_clock.restart();
		srand(time(nullptr));

		m_texture.loadFromFile("Textures/Ball.png");

		m_sprite.setTexture(m_texture);
		m_sprite.setOrigin(
			m_texture.getSize().x / 2,
			m_texture.getSize().y / 2
		);
		m_sprite.setPosition(0, 0);

		m_window.GetEventManager()->AddCallback("Move", &Game::MoveSprite, this);
	}

	void Game::Update()
	{
		m_window.Update();
	}

	void Game::Render()
	{
		m_window.BeginDraw();
		// DRAW HERE
		m_window.GetRenderWindow()->draw(m_sprite);

		m_window.EndDraw();
	}

	sf::Time Game::GetElapsed()
	{
		return m_clock.getElapsedTime();
	}

	void Game::RestartClock()
	{
		m_clock.restart();
	}

	void Game::MoveSprite(EventDetails* l_details)
	{
		sf::Vector2i mousepos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
		m_sprite.setPosition(mousepos.x, mousepos.y);
		std::cout << "Moving sprite to: " << mousepos.x << ":" << mousepos.y << std::endl;
	}

	Window* Game::GetWindow()
	{
		return &m_window;
	}
}