#include "pch.h"
#include "Game.h"

namespace Mac {

	Game::Game()
		: m_window("SFML Ch 2", sf::Vector2u(800, 600))
	{
		RestartClock();
		srand(time(NULL));

		m_ballTexture.loadFromFile("Textures/Ball.png");
		m_ballSprite.setTexture(m_ballTexture);
		m_increment = sf::Vector2i(400, 400);
	}

	void Game::HandleInput()
	{
		// Input Handling
	}

	void Game::Update()
	{
		m_window.Update();
		MoveBall();
	}

	void Game::Render()
	{
		m_window.BeginDraw();

		m_window.Draw(m_ballSprite);

		m_window.EndDraw();
	}

	Window* Game::GetWindow()
	{
		return &m_window;
	}

	sf::Time Game::GetElapsed()
	{
		return m_elapsed;
	}

	void Game::RestartClock()
	{
		m_elapsed = m_clock.restart();
	}

	void Game::MoveBall()
	{
		sf::Vector2u l_windSize = m_window.GetWindowSize();
		sf::Vector2u l_textSize = m_ballTexture.getSize();

		if ((m_ballSprite.getPosition().x >
			l_windSize.x - l_textSize.x && m_increment.x > 0) ||
			(m_ballSprite.getPosition().x < 0 && m_increment.x < 0)) {
			m_increment.x = -m_increment.x;
		}

		if ((m_ballSprite.getPosition().y >
			l_windSize.y - l_textSize.y && m_increment.y > 0) ||
			(m_ballSprite.getPosition().y < 0 && m_increment.y < 0)) {
			m_increment.y = -m_increment.y;
		}

		float fElapsed = m_elapsed.asSeconds();

		m_ballSprite.setPosition(
			m_ballSprite.getPosition().x + (m_increment.x * fElapsed),
			m_ballSprite.getPosition().y + (m_increment.y * fElapsed)
		);
	}
}