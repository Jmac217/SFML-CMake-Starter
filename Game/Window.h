#pragma once

namespace Mac {

	struct Window
	{
		Window();
		Window(const sf::String& title, const sf::Vector2u& size);
		~Window();

		void BeginDraw();
		void EndDraw();

		void Update();

		bool IsDone();
		bool IsFullscreen();

		sf::Vector2u GetWindowSize();

		void ToggleFullscreen();

		void Draw(sf::Drawable& l_drawable);

	private:
		void Setup(const std::string title, const sf::Vector2u& size);
		void Create();
		void Destroy();

		sf::RenderWindow m_window;
		sf::Vector2u m_windowSize;

		std::string m_windowTitle;

		bool m_isDone;
		bool m_isFullscreen;
	};
}