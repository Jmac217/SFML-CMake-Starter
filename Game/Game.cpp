#include "pch.h"
#include "Game.h"

namespace Mac {

	Game::Game()
		: m_window("Snake", sf::Vector2u(800, 600))
		, m_snake(m_world.GetBlockSize(), &m_textbox)
		, m_world(sf::Vector2u(800, 600))
	{
		m_clock.restart();
		srand(time(nullptr));

		m_textbox.Setup(
			5,						// links
			25,						// size
			350,					// width
			sf::Vector2f(227, 35)	// position
		);
		m_elapsed = 0.0f;

		m_textbox.Add("Welcome to SFML Snake!\nUse the W A S D keys\nOr the Arrow Keys to move\nApple Seed: " + std::to_string(time(nullptr)));
	}

	Game::~Game() {}

	void Game::HandleInput()
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W)
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)))
			&& m_snake.GetPhysicalDirection() != Direction::Down)
		{
			m_snake.SetDirection(Direction::Up);
		}
		else if
			((sf::Keyboard::isKeyPressed(sf::Keyboard::S)
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)))
			&& m_snake.GetPhysicalDirection() != Direction::Up)
		{
			m_snake.SetDirection(Direction::Down);
		}
		else if
			((sf::Keyboard::isKeyPressed(sf::Keyboard::D)
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)))
			&& m_snake.GetPhysicalDirection() != Direction::Left)
		{
			m_snake.SetDirection(Direction::Right);
		}
		else if
			((sf::Keyboard::isKeyPressed(sf::Keyboard::A)
			|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
			&& m_snake.GetPhysicalDirection() != Direction::Right)
		{
			m_snake.SetDirection(Direction::Left);
		}
	}

	void Game::Update()
	{
		m_window.Update();
		float timestep = 1.0f / m_snake.GetSpeed();
		if (m_elapsed >= timestep)
		{
			m_snake.Tick();
			m_world.Update(m_snake);
			m_elapsed -= timestep;
			if (m_snake.HasLost())
			{
				m_textbox.Add("Game Over! Score: "
					+ std::to_string((long long)m_snake.GetScore()));
				m_snake.Reset();
			}
		}
	}

	void Game::Render()
	{
		m_window.BeginDraw();

		// Draw
		m_world.Render(*m_window.GetRenderWindow());
		m_snake.Render(*m_window.GetRenderWindow());
		m_textbox.Render(*m_window.GetRenderWindow());

		m_window.EndDraw();
	}

	sf::Time Game::GetElapsed()
	{
		return m_clock.getElapsedTime();
	}

	Window* Game::GetWindow()
	{
		return &m_window;
	}

	void Game::RestartClock()
	{
		m_elapsed += m_clock.restart().asSeconds();
	}
}