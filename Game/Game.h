#include "pch.h"
#include "Window.h"
#include "EventManager.h"
#include "StateManager.h"
#include "SharedContext.h"

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		~Game() = default;

		void Update();
		void Render();
		void LateUpdate();

		sf::Time GetElapsed();

		Window* GetWindow();
	private:
		SharedContext m_context;
		Window m_window;
		StateManager m_stateManager;
		sf::Clock m_clock;
		sf::Time m_elapsed;

		void RestartClock();
	};

}