#include "pch.h"
#include "Window.h"

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		~Game() = default;

		void HandleInput();
		void Update();
		void Render();

		Window* GetWindow();

		sf::Time GetElapsed();

		void RestartClock();
	private:
		void MoveBall();

		Window m_window;
		sf::Clock m_clock;
		sf::Time m_elapsed;

		sf::Texture m_ballTexture;
		sf::Sprite m_ballSprite;
		sf::Vector2i m_increment;
	};

}