#include "pch.h"
#include "Game.h"

namespace Mac {

	Game::Game()
		: m_window("SFML Ch 6", sf::Vector2u(800, 600))
		, m_stateManager(&m_context)
	{
		m_clock.restart();
		srand(time(nullptr));

		m_context.m_window = &m_window;
		m_context.m_eventManager = m_window.GetEventManager();

		m_stateManager.SwitchTo(StateType::Intro);
	}

	void Game::Update()
	{
		m_window.Update();
		m_stateManager.Update(m_elapsed);
	}

	void Game::Render()
	{
		m_window.BeginDraw();
		// DRAW HERE
		m_stateManager.Draw();

		m_window.EndDraw();
	}

	void Game::LateUpdate()
	{
		m_stateManager.ProcessRequests();
		RestartClock();
	}

	sf::Time Game::GetElapsed()
	{
		return m_clock.getElapsedTime();
	}

	void Game::RestartClock()
	{
		m_elapsed = m_clock.restart();
	}

	Window* Game::GetWindow()
	{
		return &m_window;
	}
}