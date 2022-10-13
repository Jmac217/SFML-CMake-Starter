#include "pch.h"
#include "Window.h"
#include "EventManager.h"

#pragma once

namespace Mac {

	struct Game
	{
		Game();
		~Game() = default;

		void Update();
		void Render();

		sf::Time GetElapsed();
		void RestartClock();

		void MoveSprite(EventDetails* l_details);

		Window* GetWindow();
	private:
		Window m_window;
		sf::Clock m_clock;

		sf::Texture m_texture;
		sf::Sprite m_sprite;
	};

}